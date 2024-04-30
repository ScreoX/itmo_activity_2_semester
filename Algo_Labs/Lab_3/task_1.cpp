#include <iostream>
#include <vector>

using namespace std;


void dfs(int v, vector<vector<int>> &graph, int parent[]) {
    for (int u: graph[v]) {
        if (u != parent[v]) {
            parent[u] = v;
            dfs(u, graph, parent);
        }
    }
}

void find_prufer_code(vector<vector<int>> &graph) {
    int size = graph.size();
    int parent[size];
    parent[size - 1] = -1;
    dfs(size - 1, graph, parent);

    int pointer = -1;
    int degree[size];
    for (int i = 0; i < size; i++) {
        degree[i] = graph[i].size();
        if (degree[i] == 1 && pointer == -1) {
            pointer = i;
        }
    }

    int listok = pointer;
    int to;
    for (int i = 0; i < size - 2; i++) {
        to = parent[listok];
        cout << to + 1 << " ";
        if (--degree[to] == 1 && to < pointer) {
            listok = to;
        } else {
            pointer++;
            while (degree[pointer] != 1) {
                pointer++;
            }
            listok = pointer;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> graph(N);

    int x, y;
    for (int i = 0; i < M; i++) {
        cin >> x >> y;
        graph[x - 1].push_back(y - 1);
        graph[y - 1].push_back(x - 1);
    }

    find_prufer_code(graph);

    return 0;
}
