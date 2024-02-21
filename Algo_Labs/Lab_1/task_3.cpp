#include <iostream>
#include <vector>

void dfs(std::vector<bool>& v, std::vector<std::vector<int>>& g, int ind) {
    v[ind] = true;

    for (int j : g[ind]) {
        if (!v[j]) {
            dfs(v, g, j);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph(n);
    std::vector<bool> visited(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }

    int count = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(visited, graph, i);
            count++;
        }
    }

    std::cout << count;

    return 0;
}
