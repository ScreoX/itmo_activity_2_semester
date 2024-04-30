#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int v1, v2, w;
};

struct DSU {
    int* parent;
    int* rank;

    DSU(int n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    ~DSU() {
        delete[] parent;
        delete[] rank;
    }

    int findSet(int v) {
        if (v == parent[v]) return v;
        return parent[v] = findSet(parent[v]);
    }

    void unionSets(int a, int b) {
        a = findSet(a);
        b = findSet(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }
};

bool sorting(Edge& a, Edge& b) {
    return a.w < b.w;
}


void dfs(int x, vector<vector<pair<int,int>>> &MyMst, vector<int> &a, vector<int> &b,  vector<int> &c, vector<bool> &visited) {
    visited[x] = true;
    for (pair<int,int> i : MyMst[x]) {
        if (!visited[i.first]) {
            dfs(i.first, MyMst, a, b, c, visited);
            a[x] = max(a[x], b[i.first] + i.second - c[i.first]);
            b[x] += c[i.first];
        }
    }
    a[x] += b[x];
    c[x] = max(a[x], b[x]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<Edge> graph(M);

    int x, y, t;
    for (int i = 0; i < M; ++i) {
        cin >> x >> y >> t;
        graph[i].v1 = x - 1;
        graph[i].v2 = y - 1;
        graph[i].w = t;
    }

    DSU dsushka(N);
    sort(graph.begin(), graph.end(), sorting);

    vector<vector<pair<int,int>>> MyMst (N);

    for (auto& edge : graph) {
        if (dsushka.findSet(edge.v1) != dsushka.findSet(edge.v2)) {
            dsushka.unionSets(edge.v1, edge.v2);
            MyMst[edge.v1].emplace_back(edge.v2, edge.w);
            MyMst[edge.v2].emplace_back(edge.v1, edge.w);
        }
    }

    vector<int> odin (N, 0);
    vector<int> dva (N, 0);
    vector<int> res (N, 0);
    vector<bool> visited(N, false);
    dfs(0, MyMst, odin, dva, res, visited);

    cout << res[0];

    return 0;
}
