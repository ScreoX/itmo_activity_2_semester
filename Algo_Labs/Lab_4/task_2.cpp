#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool dfs(vector<vector<int>>& ost_graph, int s, int t, vector<bool>& visited, vector<int>& parent) {
    visited[s] = true;

    if (s == t) {
        return true;
    }

    for (int v = 0; v < ost_graph.size(); v++) {
        if (!visited[v] && ost_graph[s][v] > 0) {
            parent[v] = s;
            if (dfs(ost_graph, v, t, visited, parent)) {
                return true;
            }
        }
    }
    return false;
}

int fordFulkerson(vector<vector<int>>& graph, int s, int t) {

    vector<vector<int>> ost_graph(graph.size(), vector<int>(graph.size(), 0));
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph.size(); j++) {
            ost_graph[i][j] = graph[i][j];
        }
    }
    vector<int> parent(graph.size());

    int max_flow = 0;

    while (true) {
        vector<bool> visited(graph.size(), false);
        if (!dfs(ost_graph, s, t, visited, parent)) {
            break;
        }

        int flow = INT_MAX;

        for (int i = t; i != s; i = parent[i]) {
            int j = parent[i];
            flow = min(flow, ost_graph[j][i]);
        }

        for (int i = t; i != s; i = parent[i]) {
            int j = parent[i];
            ost_graph[j][i] -= flow;
            ost_graph[i][j] += flow;
        }

        max_flow += flow;
    }

    return max_flow;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n, vector<int>(n, 0));

    int a, b, w;

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        graph[a - 1][b - 1] = w;
    }

    cout << fordFulkerson(graph, 0, n - 1);

    return 0;
}