#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;
int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << "matrix1.txt matrix2.txt\n";
        return 1;
    }

    ifstream file1(argv[1]);
    ifstream file2(argv[2]);

    if (!file1.is_open() || !file2.is_open())
    {
        cerr << "Error: Could not open files\n";
        return 1;
    }

    int n1, m1, n2, m2;

    file1 >> n1 >> m1;
    file2 >> n2 >> m2;

    if (m1 != n2)
    {
        cerr << "Impossible multiplication: first matrix column size must be equal to second matrix row size" << endl;
        return 1;
    }

    vector<vector<int>> matrix1(n1, vector<int>(m1));
    vector<vector<int>> matrix2(n2, vector<int>(m2));

    for (int i = 0; i < n1; i++)
    {
        for (size_t j = 0; j < m1; j++)
        {
            file1 >> matrix1[i][j];
        }
        
    }

    for (int i = 0; i < n1; i++)
    {
        for (size_t j = 0; j < m1; j++)
        {
            file2 >> matrix2[i][j];
        }
        
    }
    
    file1.close();
    file2.close();

    vector<vector<int>> result(n1, vector<int>(m2, 0));

    clock_t begin = clock();

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            for (int k = 0; k < m1; k++)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    
    clock_t end = clock();
    double final_time = double(end - begin) / CLOCKS_PER_SEC;

    ofstream out_file("result.txt");
    out_file << n1 << " " << m2 << "\n";

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            out_file << "c" << i << j << " " << result[i][j] << "\n";
        }
    }
    
    out_file << fixed << setprecision(6);
    out_file << "Final time: " << final_time << " seconds\n";
    out_file.close();
    return 0;
}
