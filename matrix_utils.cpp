#include "matrix_utils.hpp"

vector<vector<double>> generateMatrix(int rows, int cols)
{
    vector<vector<double>> matrix(rows, vector<double>(cols, 0.0));
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            matrix[i][j] = (rand() % 1000) / 100.0;
        }
    }
    return matrix;
}

void saveMatrix(const vector<vector<double>> &matrix, const string &filePath)
{
    ofstream fout(filePath);
    if (!fout.is_open())
    {
        cerr << "Error: could not open file " << filePath << endl;
        return;
    }
    int rows = matrix.size();
    int cols = (rows > 0) ? matrix[0].size() : 0;
    fout << rows << " " << cols << "\n";
    for (const auto &row : matrix)
    {
        for (double value : row)
        {
            fout << value << " ";
        }
        fout << "\n";
    }
}

vector<vector<double>> readMatrix(const string &fileName, int &rows, int &cols)
{
    ifstream fin(fileName);
    if (!fin.is_open())
    {
        cerr << "Error: could not open file\n";
        exit(1);
    }
    fin >> rows >> cols;
    vector<vector<double>> matrix(rows, vector<double>(cols, 0.0));
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            fin >> matrix[i][j];
        }
    }
    fin.close();
    return matrix;
}

vector<pair<pair<int, int>, double>> computeSegment(int start, int end, int n1, int m1, int m2, const vector<vector<double>> &M1, const vector<vector<double>> &M2)
{
    vector<pair<pair<int, int>, double>> results;
    for (int i = start; i < end; ++i)
    {
        int rows = i / m2;
        int cols = i % m2;
        double sum = 0;
        for (int k = 0; k < m1; ++k)
        {
            sum += M1[rows][k] * M2[k][cols];
        }
        results.push_back({{rows, cols}, sum});
    }
    return results;
}

void saveSegment(const string &fileName, int n1, int m2, const vector<pair<pair<int, int>, double>> &segment, double elapsed_time)
{
    ofstream out(fileName);
    out << n1 << " " << m2 << endl;
    for (auto &[pos, val] : segment)
    {
        out << "c" << pos.first+1 << pos.second+1 << " " << val << endl;
    }
    out << fixed << setprecision(6) << elapsed_time << "\n";
}
