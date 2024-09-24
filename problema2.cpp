#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

void multiplicarBloques(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n, int blockSize) {
    for (int ii = 0; ii < n; ii += blockSize) {
        for (int jj = 0; jj < n; jj += blockSize) {
            for (int kk = 0; kk < n; kk += blockSize) {
                // Multiplicar bloques
                for (int i = ii; i < min(ii + blockSize, n); ++i) {
                    for (int j = jj; j < min(jj + blockSize, n); ++j) {
                        int suma = 0;
                        for (int k = kk; k < min(kk + blockSize, n); ++k) {
                            suma += A[i][k] * B[k][j];
                        }
                        C[i][j] += suma;
                    }
                }
            }
        }
    }
}

void multiplicarMatricesClasico(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;  // Inicializa la posición (i, j) de la matriz C
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
// ALEATORIO
void llenarMatriz(vector<vector<int>>& matriz, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matriz[i][j] = rand() % 100;  
        }
    }
}

int main() {
    int n, blockSize;

    cout << "tamanio de matrices (aplica para los tipos de multiplicacion): ";
    cin >> n;

    cout << "tamnio de bloque: ";
    cin >> blockSize;

    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<int>> B(n, vector<int>(n));
    vector<vector<int>> C1(n, vector<int>(n, 0));  // Matriz para la versión clásica
    vector<vector<int>> C2(n, vector<int>(n, 0));  // Matriz para la versión por bloques

    // Llenar las matrices A y B con valores aleatorios
    llenarMatriz(A, n);
    llenarMatriz(B, n);

    // Medir el tiempo de la multiplicación clásica
    auto inicioClasico = high_resolution_clock::now();
    multiplicarMatricesClasico(A, B, C1, n);
    auto finClasico = high_resolution_clock::now();
    auto duracionClasico = duration_cast<milliseconds>(finClasico - inicioClasico).count();
    cout << "multiplicacion normal " << duracionClasico << " ms" << endl;

    // Medir el tiempo de la multiplicación por bloques
    auto inicioBloques = high_resolution_clock::now();
    multiplicarBloques(A, B, C2, n, blockSize);
    auto finBloques = high_resolution_clock::now();
    auto duracionBloques = duration_cast<milliseconds>(finBloques - inicioBloques).count();
    cout << "multiplicacion por bloques: " << duracionBloques << " ms" << endl;

    return 0;
}
