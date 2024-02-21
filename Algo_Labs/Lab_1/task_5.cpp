#include <iostream>
#include <vector>

using namespace std;

void dfs(int i, vector<vector<int>>& graph, vector<int>& color, int from, bool& check) {

    color[i] = 1;

    for (int u : graph[i]) {
        if (from != u) {
            if (color[u] == 0) {
                dfs(u, graph, color, i, check);
            } else if (color[u] == 1) {
                check = true;
                return;
            }
        }
    }
    color[i] = 2;
}



int main() {

    int n, m;
    cin >> n >> m;

    std::vector<std::vector<int>> graph(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }

    bool CheckCycle = false;
    std::vector<int> color(n, 0);

    for (int i = 0; i < n; i++) {
        if (!color[i]) {
            dfs(i, graph, color, -1, CheckCycle);
        }
    }
    if (CheckCycle) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}
