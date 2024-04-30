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

bool sorting(const Edge& a, const Edge& b) {
    return a.w < b.w;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    long long N, M, K;
    cin >> N >> M >> K;
    long long size = M + K;
    vector<Edge> graph(size);

    long long a, b, t;
    long long weight = 0;

    for (long long i = 0; i < M; i++) {
        cin >> a >> b >> t;
        weight += t;
        graph[i] = {a - 1, b - 1, t};
    }
    for (long long i = 0; i < K; i++) {
        cin >> a >> b >> t;
        graph[i + M] = {a - 1, b - 1, t};
    }

    DSU dsushka(N);
    sort(graph.begin(), graph.end(), sorting);
    long long res = 0;

    for (const auto& i : graph) {
        if (dsushka.findSet(i.v1) != dsushka.findSet(i.v2)) {
            res += i.w;
            dsushka.unionSets(i.v1, i.v2);
        }
    }

    if (res < weight) {
        cout << 0;
    } else {
        cout << res - weight;
    }

    return 0;
}
