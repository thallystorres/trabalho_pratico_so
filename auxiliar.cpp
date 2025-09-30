#include "matrix_utils.cpp"

using namespace std;

void createMatrixFile(int row, int col, const string &fileName){
    vector<vector<double>> matrix = generateMatrix(row, col);
    saveMatrix(matrix, fileName);
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
    createMatrixFile(n1, m1, "matrix1.txt");
    createMatrixFile(n2, m2, "matrix2.txt");
    return 0;
}
