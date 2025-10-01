#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <iomanip>
using namespace std;

vector<vector<double>> generateMatrix(int row, int cols);
void saveMatrix(const vector<vector<double>> &matrix, const string &fileName);
vector<vector<double>> readMatrix(const string &fileName, int &rows, int &cols);
vector<pair<pair<int, int>, double>> computeSegment(int start, int end, int n1, int m1, int m2, const vector<vector<double>> &M1, const vector<vector<double>> &M2);
void saveSegment(const string &fileName, int n1, int m2, const vector<pair<pair<int, int>, double>> &segment, double elapsed_time);
