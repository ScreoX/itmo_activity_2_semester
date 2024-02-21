#include <iostream>
#include <vector>

void dfs(std::vector<bool>& v, std::vector<std::vector<int>>& g, int ind, int need_to_find) {
    v[ind] = true;

    for (int j : g[ind]) {
        if (v[need_to_find]) {
            return;
        } else if (!v[j]) {
            dfs(v, g, j, need_to_find);
        }

    }
}

int main() {

    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<std::vector<int>> graph(n);


    int a, b;

    for (int i = 0; i < m; i++) {

        std::cin >> a >> b;
        graph[a - 1].push_back(b - 1);
    }

    int x,y;
    std::vector<bool> result(q, false);


    for (int i = 0; i < q; i++) {


        std::cin >> x >> y;
        std::vector<bool> visited(n, false);

        dfs(visited, graph, x - 1, y - 1);
        visited[x - 1] = false;
        if (visited[y - 1]) {
            std::vector<bool> extra_visited(n, false);
            dfs(extra_visited, graph, y - 1, x - 1);
            if (extra_visited[x - 1]) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
