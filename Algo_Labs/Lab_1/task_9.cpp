#include <iostream>
#include <vector>

void dfs_cycle(int i, std::vector<std::vector<int>>& graph, std::vector<int>& color, int from, bool& check) {

    color[i] = 1;

    for (int u : graph[i]) {
        if (from != u) {
            if (color[u] == 0) {
                dfs_cycle(u, graph, color, i, check);
            } else if (color[u] == 1) {
                check = true;
                return;
            }
        }
    }
    color[i] = 2;
}

int dfs_connection(int u, std::vector<bool>& visited, std::vector<std::vector<int>>& g) {
    int visitedVertices = 1;
    visited[u] = true;

    for (int v : g[u]) {
        if (!visited[v]) {
            visitedVertices += dfs_connection(v, visited, g);
        }
    }

    return visitedVertices;
}

int main() {

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph(n);
    std::vector<bool> visited(n);
    std::vector<int> color(n, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }

    bool CheckCycle = false;

    for (int i = 0; i < n; i++) {
        if (!color[i]) {
            dfs_cycle(i, graph, color, -1, CheckCycle);
        }
    }

    int count_v = dfs_connection(0, visited, graph);

    bool CheckConnection;
    if (count_v == n) {
        CheckConnection = true;
    } else {
        CheckConnection = false;
    }

    if (n == m && CheckConnection && CheckCycle) {
        std::cout << "ARCHIMEDES";
    } else {
        std::cout << "EUCLID";
    }

    return 0;
}
