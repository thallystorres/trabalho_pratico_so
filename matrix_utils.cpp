#include "matrix_utils.hpp"
#include <fstream>
#include <cstdlib>
#include <iostream>

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
    if(!fin.is_open()){
        cerr << "Error: could not open file\n";
        exit(1);
    }
    fin >> rows >> cols;
    vector<vector<double>> matrix(rows, vector<double>(cols, 0.0));
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