#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int N = 3000;
const int TRIES_NUM = 5;

void fillArrayRandomly(double **arr, int sz) {
    srand((unsigned)time( NULL ));
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            arr[i][j] = (double)rand() / 12345.0;
        }
    }
}

void ZeroMatrix(double **arr, int sz) {
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            arr[i][j] = 0;
        }
    }
}

double calcMatMulTime_ijk(double **a, double **b, double **c, int sz) {
    ZeroMatrix(c, sz);
    auto start = high_resolution_clock::now();
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            for (int k = 0; k < sz; ++k) {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    return duration.count() / 1000;
}

double calcMatMulTime_jik(double **a, double **b, double **c, int sz) {
    ZeroMatrix(c, sz);
    auto start = high_resolution_clock::now();
    for (int j = 0; j < sz; ++j) {
        for (int i = 0; i < sz; ++i) {
            for (int k = 0; k < sz; ++k) {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    return duration.count() / 1000;
}

double calcMatMulTime_kij(double **a, double **b, double **c, int sz) {
    ZeroMatrix(c, sz);
    auto start = high_resolution_clock::now();
    for (int k = 0; k < sz; ++k) {
        for (int j = 0; j < sz; ++j) {
            for (int i = 0; i < sz; ++i) {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    return duration.count() / 1000;
}

int main() {
    int n;
    cout << "Enter arrays size: ";
    cin >> n;
    double **A, **B, **C;
    A = new double *[N];
    B = new double *[N];
    C = new double *[N];
    for (int i = 0; i < N; ++i) {
        A[i] = new double[N];
        B[i] = new double[N];
        C[i] = new double[N];
    }
    fillArrayRandomly(A, n);
    fillArrayRandomly(B, n);
    double res = 0;
    for (int t = 0; t < TRIES_NUM; ++t) {
        double time_taken = calcMatMulTime_ijk(A, B, C, n);
        res += time_taken;
    }
    res /= TRIES_NUM;
    cout << "Average working time ijk: " << res << " ms" << endl;

    res = 0;
    for (int t = 0; t < TRIES_NUM; ++t) {
        double time_taken = calcMatMulTime_jik(A, B, C, n);
        res += time_taken;
    }
    res /= TRIES_NUM;
    cout << "Average working time jik: " << res << " ms" << endl;

    res = 0;
    for (int t = 0; t < TRIES_NUM; ++t) {
        double time_taken = calcMatMulTime_kij(A, B, C, n);
        res += time_taken;
    }
    res /= TRIES_NUM;
    cout << "Average working time kij: " << res << " ms" << endl;
    return 0;
}