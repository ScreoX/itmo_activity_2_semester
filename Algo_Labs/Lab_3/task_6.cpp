#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int from, to, weight, index;
};

bool sorting(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

struct DSU {
private:
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int findSet(int x) {
        if (x != parent[x])
            parent[x] = findSet(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = findSet(x);
        int rootY = findSet(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY])
                swap(rootX, rootY);
            parent[rootY] = rootX;
            if (rank[rootX] == rank[rootY])
                rank[rootX]++;
        }
    }
};

pair<int, int> kruskal(vector<Edge>& edges, int n, int m) {
    int minCost = 0, secondCost = 0;
    DSU dsushka(n);

    int i = 0;
    vector<bool> used(m, false);
    vector<Edge> ost(n - 1);

    for (Edge& edge : edges) {
        if (dsushka.findSet(edge.from) != dsushka.findSet(edge.to)) {
            dsushka.unite(edge.from, edge.to);
            minCost += edge.weight;
            used[edge.index] = true;
            ost[i] = edge;
            ++i;
        }
        if (i == n - 1) {
            break;
        }
    }

    int res = INT_MAX;
    for (Edge edge : edges) {
        if (used[edge.index]) {
            secondCost = 0;
            i = 0;
            int pre = edge.weight;
            edges[edge.index] = {edge.from, edge.to, INT_MAX};
            sort(edges.begin(), edges.end(), sorting);
            vector<bool> pre_used(m, false);
            DSU dsushka_2(n);
            for (Edge &e: edges) {
                if (dsushka_2.findSet(e.from) != dsushka_2.findSet(e.to)) {
                    dsushka_2.unite(e.from, e.to);
                    secondCost += e.weight;
                    pre_used[e.index] = true;
                    ++i;
                }
                if (i == n - 1) {
                    break;
                }
            }

            edges[m - 1] = {edge.from, edge.to, pre};
            res = min(secondCost, res);
            sort(edges.begin(), edges.end(), sorting);
        }
    }
    return {minCost, res};

}

int main() {
    int N, M;
    cin >> N >> M;

    vector<Edge> edges;
    for (int i = 0; i < M; ++i) {
        int A, B, C;
        cin >> A >> B >> C;
        edges.emplace_back(A - 1, B - 1, C);
    }

    sort(edges.begin(), edges.end(), sorting);

    for (int i = 0; i < edges.size(); i++) {
        edges[i].index = i;
    }

    pair<int, int> result = kruskal(edges, N, M);

    cout << result.first << " " << result.second << endl;

    return 0;
}