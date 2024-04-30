#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<int> ans;

int cnt = 0;

void dfs(std::vector<bool>& v, std::vector<std::vector<int>>& g, int ind) {
    v[ind] = true;

    for (int j : g[ind]) {
        if (!v[j]) {
            dfs(v, g, j);
        }
    }
}

void dfs_check(std::vector<bool>& v, std::vector<std::vector<int>>& g, int ind) {
    v[ind] = true;

    for (int j : g[ind]) {
        if (!v[j]) {
            ++cnt;
            dfs(v, g, j);
        }
    }
}

void findEulerPath(int v, vector<vector<int>>& graph) {
    stack<int> S;
    S.push(v);

    while (!S.empty()) {
        int w = S.top();
        bool found_edge = false;

        for (int i = 0; i < graph[w].size(); ++i) {
            int u = graph[w][0];
            if (find(graph[u].begin(), graph[u].end(), w) != graph[u].end()) {
                graph[w].erase(graph[w].begin() + i);
                graph[u].erase(find(graph[u].begin(), graph[u].end(), w));
                S.push(u);
                found_edge = true;
                break;
            }
        }

        if (!found_edge) {
            ans.push_back(w + 1);
            S.pop();
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> graph(N);
    vector<bool> visited(N,false);

    int x, y;
    for (int i = 0; i < M; i++) {
        cin >> x >> y;
        graph[x - 1].push_back(y - 1);
        graph[y - 1].push_back(x - 1);
    }

    for (int u = 0; u < graph.size(); ++u) {
        if (graph[u].size() % 2 == 1) {
            cout << ":(";
            return 0;
        }
    }

    dfs(visited, graph, 0);

    vector<int> components(N);
    for (int i = 0; i < graph.size(); i++) {
        if (!visited[i]) {
            dfs_check(visited, graph, i);
        }
    }

    if (cnt != 0) {
        cout << ":(";
        return 0;
    }

    findEulerPath(0, graph);

    for (int i = 0; i < ans.size(); i++) {
        cout << ans[ans.size() - 1 - i] << " ";
    }

    return 0;
}
