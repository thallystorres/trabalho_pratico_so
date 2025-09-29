#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cmath>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

struct Task
{
    int id;
    int start;
    int end;
    int n1, m1, m2;
    vector<vector<double>> *M1;
    vector<vector<double>> *M2;
};


vector<vector<double>> readMatrix(const string &fileName, int &rows, int &cols){
    ifstream fin(fileName);
    fin >> rows >> cols;
    vector<vector<double>> matrix(rows, vector<double>(cols));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fin >> matrix[i][j];
        }
    }
    fin.close();
    return matrix;
}

double computeAndSave(const Task &task){
    auto start = chrono::high_resolution_clock::now();
    
    vector<vector<double>> R(task.n1, vector<double>(task.m2, 0.0));
    for (int idx = task.start; idx < task.end; idx++)
    {
        int i = idx / task.m2;
        int j = idx % task.m2;
        double sum = 0;
        for (int k = 0; k < task.m1; k++)
        {
            sum += (*(task.M1))[i][k] * (*(task.M2))[k][j];
        }
        R[i][j] = sum;
    }
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;

    string fname = "result" + to_string(task.id) + ".txt";
    ofstream fout(fname);

    fout << task.n1 << " " << task.m2 << "\n";
    for (int idx = task.start; idx < task.end; idx++)
    {
        int i = idx / task.m2;
        int j = idx % task.m2;
        fout << R[i][j] << " ";
        if(j == task.m2 - 1) fout << "\n";
    }
    fout << elapsed.count() << "\n";
    fout.close();

    return elapsed.count();
}

int main(int argc, char const *argv[])
{
    if(argc != 4){
        cerr << "Usage: " << argv[0] << " matrix1.txt matrix2.txt P\n";
    }
    string file1 = argv[1];
    string file2 = argv[2];
    int P = stoi(argv[3]);

    int n1, m1, m2, m1_check;

    vector<vector<double>> M1 = readMatrix(file1, n1, m1);

    vector<vector<double>> M2 = readMatrix(file2, m1_check, m2);

    if(m1 != m1_check){
        cerr << "Error: incompatible dimensions\n";
        return 1;
    }

    int total = n1 * m2;
    int numTasks = (int)ceil((double)total / P);

    vector<pid_t> children;
    vector<int> pipes(numTasks * 2);

    for (int t = 0; t < numTasks; t++)
    {
        int fds[2];
        if(pipe(fds) == -1){
            cerr << "Error: couldn't create pipe\n";
            return 1;
        }

        pipes[t * 2] = fds[0];
        pipes[t * 2 + 1] = fds[1];
        Task task;
        task.id = t;
        task.start = t * P;
        task.end = min((t + 1) * P, total);
        task.n1 = n1;
        task.m1 = m1;
        task.m2 = m2;
        task.M1 = &M1;
        task.M2 = &M2;
        
        pid_t pid = fork();

        if(pid == 0){
            close(pipes[t * 2]);
            double delta = computeAndSave(task);
            write(pipes[t * 2 + 1], &delta, sizeof(double));
            close(pipes[t * 2 + 1]);
            _exit(0);
        }else if(pid > 0){
            children.push_back(pid);
            close(pipes[t * 2 + 1]);
        } else {
            cerr << "Fork error\n";
            return 1;
        }
    }
    
    double maxTime = 0.0;
    for (int p = 0; p < numTasks; p++)
    {
        double t;
        read(pipes[p * 2], &t, sizeof(double));
        maxTime = max(maxTime, t);
        close(pipes[p * 2]);
    }

    for(pid_t pid : children){
        waitpid(pid, nullptr, 0);
    }
    
    cout << maxTime << "\n";
    return 0;
}
