#include <matrix_utils.cpp>
#include <chrono>
#include <cmath>
#include <thread>

using namespace std;

struct ThreadData
{
    int id;
    int start;
    int end;
    int n1, m1, m2;
    vector<vector<double>> *M1;
    vector<vector<double>> *M2;
    vector<vector<double>> *R;
};

void worker(ThreadData data)
{
    auto start = chrono::high_resolution_clock::now();
    for (int idx = data.start; idx < data.end; idx++)
    {
        int i = idx / data.m2;
        int j = idx % data.m2;
        double sum = 0;
        for (int k = 0; k < data.m1; k++)
        {
            sum += (*(data.M1))[i][k] * (*(data.M2))[k][j];
        }
        (*(data.R))[i][j] = sum;
    }
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;

    string fname = "result_" + to_string(data.id) + ".txt";
    ofstream fout(fname);

    fout << data.n1 << " " << data.m2 << "\n";
    for (int idx = data.start; idx < data.end; idx++)
    {
        int i = idx / data.m2;
        int j = idx % data.m2;
        fout << (*(data.R))[i][j] << " ";
        if (j == data.m2 - 1)
            fout << "\n";
    }
    fout << elapsed.count() << "\n";
    fout.close();
}

int main(int argc, char const *argv[])
{
    if (argc != 4)
    {
        cerr << "Usage: " << argv[0] << "matrix1.txt matrix2.txt P\n";
        return 1;
    }

    string file1 = argv[1];
    string file2 = argv[2];
    int P = stoi(argv[3]);

    int n1, m1, m2, m1_check;

    vector<vector<double>> M1 = readMatrix(file1, n1, m1);

    vector<vector<double>> M2 = readMatrix(file2, m1_check, m2);

    if (m1_check != m1)
    {
        cerr << "Error: incompatible dimensions\n";
        return 1;
    }

    vector<vector<double>> R(n1, vector<double>(m2, 0.0));
    int total = n1 * m2;
    int numThreads = (int)ceil((double)total / P);

    vector<thread> threads;
    vector<ThreadData> td(numThreads);

    for (int t = 0; t < numThreads; t++)
    {
        td[t].id = t;
        td[t].start = t * P;
        td[t].end = min((t + 1) * P, total);
        td[t].n1 = n1;
        td[t].m1 = m1;
        td[t].m2 = m2;
        td[t].M1 = &M1;
        td[t].M2 = &M2;
        td[t].R = &R;
        threads.emplace_back(worker, td[t]);
    }

    for (auto &th : threads)
    {
        th.join();
    }

    return 0;
}
