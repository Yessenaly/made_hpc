#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int SZ = 10;
const double EPS = 1e-6;

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

void print_vec(double *a, int sz) {
    for (int i = 0; i < sz; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}

void ZeroVec(double *vec, int sz) {
    for (int i = 0; i < sz; ++i) {
        vec[i] = 0;
    }
}

void clone_vec(double *a, double*b, int sz) {
    for (int i = 0; i < sz; ++i) {
        a[i] = b[i];
    }
}

void norm_vec(double *a, int sz) {
    double sum = 0;
    for (int i = 0; i < sz; ++i) {
        sum += abs(a[i]);
    }
    for (int i = 0; i < sz; ++i) {
        a[i] = a[i] / sum;
    }
}

void generate_random_vec(double *vec, int sz) {
    for (int i = 0; i < sz; ++i) {
        vec[i] = (double)rand() / 12345;
    }
}

double diff(double *a, double *b, int sz) {
    double res = 0;
    for (int i = 0; i < sz; ++i) {
        res += abs(a[i] - b[i]);
    }
    return res;
}

void ZeroMatrix(double *arr, int sz) {
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            arr[i * sz + j] = 0;
        }
    }
}

void matmulvec(double *a, double *vec, double *res, int sz) {
    ZeroVec(res, sz);
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            res[i] += a[i * sz + j] * vec[j];
        }
    }
}

double* naive_rank(double *a, int sz) {
    double *res = new double[sz];
    ZeroVec(res, sz);
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            res[i] += a[j * sz + i];
        }
    }
    return res;
}

bool compare(pair<int, double> a, pair<int, double> b) {
    return b.second <= a.second;
}

int main() {
    double *graph = new double[SZ * SZ];
    ZeroMatrix(graph, SZ);
    generate_random_graph(graph, SZ);
    double *naive = naive_rank(graph, SZ);
    vector<pair<int, double> >naive_rank;
    for (int i = 0; i < SZ; ++i) {
        naive_rank.push_back(make_pair(i, naive[i]));
    }

    sort(naive_rank.begin(), naive_rank.end(), compare);
    cout << "Naive ranking: " << endl;
    for (int i = 0; i < naive_rank.size(); ++i) {
        cout << "(" << naive_rank[i].first << ", " << naive_rank[i].second << ") ";
    }
    cout << endl;

    double *x = new double[SZ];
    double *y = new double[SZ];
    ZeroVec(x, SZ);
    generate_random_vec(x, SZ);
    while(true) {
        double *old_x = new double[SZ];
        clone_vec(old_x, x, SZ);
        matmulvec(graph, x, y, SZ);
        clone_vec(x, y, SZ);
        norm_vec(x, SZ);
        double difference = diff(x, old_x, SZ);
        cout << "Difference x_{i+1} - x_i: " << difference << endl;
        if (difference < EPS) {
            break;
        }
    }

    vector<pair<int, double> >page_rank;
    for (int i = 0; i < SZ; ++i) {
        page_rank.push_back(make_pair(i, x[i]));
    }

    sort(page_rank.begin(), page_rank.end(), compare);
    cout << "Pagerank: " << endl;
    for (int i = 0; i < page_rank.size(); ++i) {
        cout << "(" << page_rank[i].first << ", " << page_rank[i].second << ") ";
    }
    cout << endl;
    return 0;
}