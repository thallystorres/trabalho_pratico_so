#include "matrix_utils.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << "matrix1.txt matrix2.txt\n";
        return 1;
    }

    int n1, m1, n2, m2;
    vector<vector<double>> M1 = readMatrix(argv[1], n1, m1);
    vector<vector<double>> M2 = readMatrix(argv[2], n2, m2);

    if (m1 != n2)
    {
        cerr << "Impossible multiplication: first matrix column size must be equal to second matrix row size" << endl;
        return 1;
    }

    int total_elements = n1 * m2;

    auto start_time = chrono::high_resolution_clock::now();

    auto segment = computeSegment(0, total_elements, n1, m1, m2, M1, M2);

    auto end_time = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end_time - start_time;

    saveSegment("sequential/result_sequential.txt", n1, m2, segment, elapsed.count());

    cout << fixed << setprecision(6) << "Maior tempo de processamento de sequencial: " << elapsed.count() << " segundos\n";
    return 0;
}
