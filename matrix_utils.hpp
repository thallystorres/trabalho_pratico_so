#pragma once
#include <vector>
#include <string>
using namespace std;

vector<vector<double>> generateMatrix(int row, int cols);
void saveMatrix(const vector<vector<double>> &matrix, const string &fileName);
vector<vector<double>> readMatrix(const string &fileName, int &rows, int &cols);