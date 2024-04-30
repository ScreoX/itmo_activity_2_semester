#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    long long v1, v2, w;
};

struct DSU {
    long long* parent;
    long long* rank;

    DSU(long long n) {
        parent = new long long[n];
        rank = new long long[n];
        for (long long i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    ~DSU() {
        delete[] parent;
        delete[] rank;
    }

    long long findSet(long long v) {
        if (v == parent[v]) {
            return v;
        }
        return parent[v] = findSet(parent[v]);
    }

    void unionSets(long long a, long long b) {
        a = findSet(a);
        b = findSet(b);

        if (a != b) {
            if (rank[a] > rank[b]) {
                swap(a, b);
            }
            parent[b] = a;
            if (rank[a] == rank[b]) {
                rank[a]++;
            }
        }
    }
};

bool sorting(Edge& a, Edge& b) {
    return a.w < b.w;
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long N, M;
    cin >> N >> M;
    vector<Edge> graph(M);

    long long a, b, t;
    for (long long i = 0; i < M; i++) {
        cin >> a >> b >> t;
        graph[i] = {a - 1, b - 1, t};
    }

    DSU dsushka(N);
    sort(graph.begin(), graph.end(), sorting);
    long long res = 0;

    for (auto i : graph) {
        if (dsushka.findSet(i.v1) != dsushka.findSet(i.v2)) {
            res += i.w;
            dsushka.unionSets(i.v1, i.v2);
        }
    }

    cout << res;

    return 0;
}
