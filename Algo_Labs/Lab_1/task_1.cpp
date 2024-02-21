#include <iostream>
#include <vector>

std::vector<int> ans;
int count;

void dfs(std::vector<bool>& v, std::vector<std::vector<int>>& g, int ind) {
    v[ind] = true;

    for (int j : g[ind]) {
        if (!v[j]) {
            dfs(v, g, j);
        }
    }

    ans[ind] = count--;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph(n);
    std::vector<bool> visited(n);
    ans.resize(n);
    count = n - 1;

    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        graph[a - 1].push_back(b - 1);
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(visited, graph, i);
        }
    }

    for (int i = 0; i < n; i++) {
        std::cout << ans[i] + 1<< " ";
    }


    return 0;
}
