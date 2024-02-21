#include <iostream>
#include <vector>
#include "queue"


void bfs(int ind, std::vector<std::vector<int>>& g, std::vector<int>& dist) {


    dist[ind] = 0;
    std::queue<int> q;
    q.push(ind);

    while (!q.empty()) {
        int i = q.front();
        q.pop();
        for (int u : g[i]) {
            if (dist[u] > dist[i] + 1) {
                dist[u] = dist[i] + 1;
                q.push(u);
            }
        }
    }

}

int main() {
    int n;
    std::cin >> n;
    int m, k;
    std::cin >> m >> k;

    std::vector<std::vector<int>> graph(n);
    std::vector<int> dist(n, INT_MAX);

    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }

    bfs(0, graph, dist);

    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (dist[i] == k && dist[i] != INT_MAX) {
            ++count;
            std::cout << i + 1 << '\n';
        }
    }
    if (count == 0) {
        std::cout << "NO";
    }

    return 0;
}
