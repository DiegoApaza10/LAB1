#include <iostream>
#include <chrono> 
#include <vector> 

#define MAX 50000

// Inicializar A, x y y
void initialize(std::vector<std::vector<double>>& A, std::vector<double>& x, std::vector<double>& y) {
    for (int i = 0; i < MAX; ++i) {
        x[i] = 1.0;  // Inicializar x en 1
        y[i] = 0.0;  // Inicializar y en 0
        for (int j = 0; j < MAX; ++j) {
            A[i][j] = 1.0;  // Inicializar A con un valor arbitrario, en este caso 1
        }
    }
}

// Primera pareja de bucles
void first_pair_loops(const std::vector<std::vector<double>>& A, const std::vector<double>& x, std::vector<double>& y) {
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            y[i] += A[i][j] * x[j];
        }
    }
}

// Segunda pareja de bucles
void second_pair_loops(const std::vector<std::vector<double>>& A, const std::vector<double>& x, std::vector<double>& y) {
    for (int j = 0; j < MAX; ++j) {
        for (int i = 0; i < MAX; ++i) {
            y[i] += A[i][j] * x[j];
        }
    }
}

int main() {
    // Asignación dinámica de memoria
    std::vector<std::vector<double>> A(MAX, std::vector<double>(MAX));
    std::vector<double> x(MAX), y(MAX);

    // Inicializar A, x y y
    initialize(A, x, y);

    // Medir tiempo de la primera pareja de bucles
    auto start = std::chrono::high_resolution_clock::now();
    first_pair_loops(A, x, y);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_first = end - start;
    std::cout << "Tiempo de la primera pareja de bucles: " << elapsed_first.count() << " segundos.\n";

    // Reiniciar y a 0
    std::fill(y.begin(), y.end(), 0.0);

    // Medir tiempo de la segunda pareja de bucles
    start = std::chrono::high_resolution_clock::now();
    second_pair_loops(A, x, y);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_second = end - start;
    std::cout << "Tiempo de la segunda pareja de bucles: " << elapsed_second.count() << " segundos.\n";

    return 0;
}
