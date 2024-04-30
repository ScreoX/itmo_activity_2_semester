#include <iostream>
#include <vector>
#include "algorithm"

std::vector<int> enter, ret;

void dfs(int i, int& t, std::vector<bool> &visited, std::vector<std::vector<int>> &graph, int p, std::vector<std::vector<int>>& ans) {
    visited[i] = true;
    enter[i] =ret[i] = t;
    ++t;
    for (int j: graph[i]) {
        if (j == p) { continue; }
        if (visited[j]) {
            enter[i] = std::min(enter[i], enter[j]);
        }
        else {
            dfs(j, t, visited, graph, i, ans);
            enter[i] = std::min(enter[i], enter[j]);
            if (enter[j] > ret[i]) {
                ans.push_back({std::min(i, j), std::max(i,j)});
            }
        }
    }
}

void find_bridges(std::vector<bool> &visited, std::vector<std::vector<int>> &graph, std::vector<std::vector<int>>& ans) {
    int t = 1;
    for (int i = 0; i < visited.size(); ++i) {
        if (!visited[i]) {
            dfs(i, t, visited, graph, -1, ans);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph(n);
    std::vector<bool> visited(n, false);
    std::vector<std::vector<int>> ans;

    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        graph[x - 1].push_back(y - 1);
        graph[y - 1].push_back(x - 1);
    }

    enter.resize(n, 0);
    ret.resize(n, 0);

    find_bridges(visited, graph, ans);

    std::sort(ans.begin(), ans.end());

    for (int i = 0; i < ans.size(); i++) {
        std::cout << ans[i][0] + 1 << " " << ans[i][1] + 1<< "\n";
    }
    return 0;
}