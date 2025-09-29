#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// Generate matrix with random values

vector<vector<int>> generateMatrix(int rows, int columns)
{
    vector<vector<int>> matrix(rows, vector<int>(columns));
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            matrix[i][j] = rand() % 100;
        }
    }
    return matrix;
}

void saveMatrix(const vector<vector<int>> &matrix, const string &filePath)
{
    ofstream _file(filePath);
    if (!_file.is_open())
    {
        cerr << "Error: could not open file " << filePath << endl;
        return;
    }
    int rows = matrix.size();
    int columns = (rows > 0) ? matrix[0].size() : 0;
    _file << rows << " " << columns << "\n";

    for (const auto &row : matrix)
    {
        for (int value : row)
        {
            _file << value << " ";
        }
        _file << "\n";
    }

    cout << "Matrix saved in " << filePath << endl;
}

int main(int argc, char const *argv[])
{
    if (argc != 5)
    {
        cerr << "Usage: " << argv[0] << " <rows_M1> <columns_M1> <rows_M2> <columns_M2>" << endl;
    }
    int n1, m1, n2, m2;
    try{
        n1 = stoi(argv[1]);
        m1 = stoi(argv[2]);
        n2 = stoi(argv[3]);
        m2 = stoi(argv[4]);
    } catch (const exception& e) {
        cerr << "Error: The arguments must be integer" << endl;
        return 1;
    }
    srand(0);
    vector<vector<int>> matrix1 = generateMatrix(n1, m1);
    saveMatrix(matrix1, "matrix1.txt");
    vector<vector<int>> matrix2 = generateMatrix(n1, m1);
    saveMatrix(matrix2, "matrix2.txt");
    return 0;
}
