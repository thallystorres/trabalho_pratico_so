#include "matrix_utils.cpp"
#include <chrono>
#include <iomanip>

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
    if(m1 != n2)
    {
        cerr << "Impossible multiplication: first matrix column size must be equal to second matrix row size" << endl;
        return 1;
    }


    vector<vector<double>> result(n1, vector<double>(m2, 0));

    auto begin = chrono::high_resolution_clock::now();

    // Multiplicação de matrizes
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            for (int k = 0; k < m1; k++)
            {
                result[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> final_time = end - begin;

    ofstream out_file("result.txt");
    out_file << n1 << " " << m2 << "\n";
        out_file << fixed << setprecision(3);

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            out_file << "c" << i+1 << j+1 << " " << result[i][j] << "\n";
        }
    }
    
    out_file << fixed << setprecision(6);
    out_file << "Final time: " << final_time.count() << " seconds\n";
    out_file.close();
    return 0;
}
