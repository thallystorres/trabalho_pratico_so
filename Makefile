CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Diretórios
EXECUTABLES_DIR = executables
CREATED_DIR = created
PROCESSES_DIR = processes
SEQUENTIAL_DIR = sequential
THREADS_DIR = threads

# Alvos principais
all: dirs auxiliar sequencial thread processos max_time

# Cria todos os diretórios de saída
dirs:
	mkdir -p $(EXECUTABLES_DIR) $(CREATED_DIR) $(SEQUENTIAL_DIR) $(THREADS_DIR) $(PROCESSES_DIR)

# Compila o programa max_time
max_time: dirs max_time.cpp matrix_utils.cpp
	$(CXX) $(CXXFLAGS) max_time.cpp matrix_utils.cpp -o $(EXECUTABLES_DIR)/max_time

# Compila o programa auxiliar
auxiliar: dirs auxiliar.cpp matrix_utils.cpp
	$(CXX) $(CXXFLAGS) auxiliar.cpp matrix_utils.cpp -o $(EXECUTABLES_DIR)/auxiliar

# Compila o programa sequencial
sequencial: dirs sequencial.cpp matrix_utils.cpp
	$(CXX) $(CXXFLAGS) sequencial.cpp matrix_utils.cpp -o $(EXECUTABLES_DIR)/sequencial

# Compila o programa com threads
thread: dirs thread.cpp matrix_utils.cpp
	$(CXX) $(CXXFLAGS) thread.cpp matrix_utils.cpp -o $(EXECUTABLES_DIR)/thread -pthread

# Compila o programa com processos
processos: dirs processos.cpp matrix_utils.cpp
	$(CXX) $(CXXFLAGS) processos.cpp matrix_utils.cpp -o $(EXECUTABLES_DIR)/processos

# Limpeza
clean:
	rm -rf $(EXECUTABLES_DIR)/*
	rm -rf $(CREATED_DIR)/*
	rm -rf $(THREADS_DIR)/*
	rm -rf $(SEQUENTIAL_DIR)/*
	rm -rf $(PROCESSES_DIR)/*

.PHONY: all clean dirs auxiliar sequencial thread processos max_time
