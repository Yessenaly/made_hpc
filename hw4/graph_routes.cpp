#include <iostream>
#include <ctime>

using namespace std;

const int SZ = 10;
const int m = 10;

void generate_random_graph(double *a, int sz) {
    // Evety column sum must be greater than zero for pagerank algorithm
    for (int i = 0; i < sz; ++i) {
        // Edges number which can be greater than sz
        int n = rand() % (sz + sz / 2) + 1;
        for (int j = 0; j < n; ++j) {
            int nbr = rand() % sz;
            a[nbr * sz + i]++;
        }
    }
}

void ZeroMatrix(double *arr, int sz) {
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            arr[i * sz + j] = 0;
        }
    }
}

double* matmul(double *a, double *b, int sz) {
    double *c = new double[sz * sz];
    ZeroMatrix(c, sz);
    for (int k = 0; k < sz; ++k) {
        for (int j = 0; j < sz; ++j) {
            for (int i = 0; i < sz; ++i) {
                c[i * sz + j] = c[i * sz + j] + a[i * sz + k] * b[k * sz + j];
            }
        }
    }
    return c;
}

double* power(double *a, int sz, int n) {
    // Matrix power with log2(n) asymptotic
    if (n == 1) {
        return a;
    }

    if (n % 2 == 1) {
        double *res = power(a, sz, n - 1);
        return matmul(a, res, sz);
    }
    else {
        double *res = power(a, sz, n / 2);
        return matmul(res, res, sz);
    }
}

int main() {
    double *graph = new double[SZ * SZ];
    ZeroMatrix(graph, SZ);
    generate_random_graph(graph, SZ);
    double *routes = power(graph, SZ, m);
    for (int i = 0; i < SZ; ++i) {
        for (int j = 0; j < SZ; ++j) {
            cout << graph[i * SZ + j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < SZ; ++i) {
        for (int j = 0; j < SZ; ++j) {
            cout << routes[i * SZ + j] << " ";
        }
        cout << endl;
    }
    return 0;
}