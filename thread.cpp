#include "matrix_utils.hpp"
#include <chrono>
#include <cmath>
#include <thread>
#include <iomanip>

using namespace std;

struct threadData
{
    int id, start, end, n1, m1, m2;
    vector<vector<double>> *M1;
    vector<vector<double>> *M2;
};

void threadWorker(threadData data)
{
    auto start_time = chrono::high_resolution_clock::now();
    auto segment = computeSegment(data.start, data.end, data.n1, data.m1, data.m2, *data.M1, *data.M2);
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end_time - start_time;
    saveSegment("threads/result_thread_" + to_string(data.id) + ".txt", data.n1, data.m2, segment, elapsed.count());
}

int main(int argc, char const *argv[])
{
    if (argc != 4)
    {
        cerr << "Usage: " << argv[0] << "matrix1.txt matrix2.txt P\n";
        return 1;
    }

    int n1, m1, n2, m2;
    vector<vector<double>> M1 = readMatrix(argv[1], n1, m1);
    vector<vector<double>> M2 = readMatrix(argv[2], n2, m2);

    if (m1 != n2)
    {
        cerr << "Incompatible matrix sizes.\n";
        return 1;
    }

    int P = stoi(argv[3]);
    int total_elements = n1 * m2;
    int num_threads = ceil((double)total_elements / P);
    vector<thread> threads;

    for (int t = 0; t < num_threads; ++t)
    {
        int start_index = t * P;
        int end_index = min(start_index + P, total_elements);
        threads.emplace_back(threadWorker, threadData{t, start_index, end_index, n1, m1, m2, &M1, &M2});
    }

    for (auto &th : threads)
    {
        th.join();
    }
}
