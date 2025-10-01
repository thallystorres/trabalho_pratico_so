#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

void process_dir(const string& dir, const string& prefix, double& max_time, bool& found) {
    for (const auto &entry : fs::directory_iterator(dir)) {
        string filename = entry.path().string();
        if (filename.find(prefix) == string::npos)
            continue;
        if (filename.find(".txt") == string::npos)
            continue;
        ifstream fin(filename);
        if (!fin.is_open()) {
            cerr << "Nao foi possivel abrir o arquivo: " << filename << endl;
            continue;
        }
        string line, last_line;
        while (getline(fin, line)) {
            last_line = line;
        }
        fin.close();
        try {
            double thread_time = stod(last_line);
            if (!found || thread_time > max_time) {
                max_time = thread_time;
                found = true;
            }
        } catch (...) {
            cerr << "Erro ao ler tempo do arquivo: " << filename << endl;
        }
    }
}

int main() {
    double max_thread = 0.0, max_process = 0.0;
    bool found_thread = false, found_process = false;
    if (fs::exists("threads") && fs::is_directory("threads")) {
        process_dir("threads", "result_thread_", max_thread, found_thread);
    }
    if (fs::exists("processes") && fs::is_directory("processes")) {
        process_dir("processes", "result_process_", max_process, found_process);
    }
    if (found_thread) {
        cout << "Maior tempo de processamento de thread: " << fixed << setprecision(6) << max_thread << " segundos" << endl;
    } else {
        cout << "Nenhum tempo de thread encontrado." << endl;
    }
    if (found_process) {
        cout << "Maior tempo de processamento de processo: " << fixed << setprecision(6) << max_process << " segundos" << endl;
    } else {
        cout << "Nenhum tempo de processo encontrado." << endl;
    }
    return 0;
}
