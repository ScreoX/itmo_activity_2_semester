#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> colors;
int color = 0;

void paint(int v, stack<int>& stachik) {
    color++;
    int last = -1;
    while (last != v && !stachik.empty()) {
        colors[stachik.top()] = color;
        last = stachik.top();
        stachik.pop();
    }
}

int t = 0;

void dfs(int v, int parent, vector<int>& enter, vector<int>& ret, stack<int>& stachik, vector<vector<int>>& graph) {
    t++;
    stachik.push(v);
    enter[v] = t;
    ret[v] = t;

    for (int u : graph[v]) {
        if (u == parent) {
            continue;
        }

        if (enter[u] != 0) {
            ret[v] = min(ret[v], enter[u]);
        } else {
            dfs(u, v, enter, ret, stachik, graph);
            ret[v] = min(ret[v], ret[u]);
            if (ret[u] > enter[v]) {
                paint(u, stachik);
            }
        }
    }
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> graph(n + 1);
    stack<int> mystack;

    int x, y;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    vector<int> enter(n + 1);
    vector<int> ret(n + 1);
    colors.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        if (!enter[i]) {
            dfs(i, -1, enter, ret, mystack, graph);
        }
    }

    vector<bool> ans(q);
    int a, b;
    for (int i = 0; i < q; ++i) {
        cin >> a >> b;
        if (colors[a] != colors[b]) {
            ans[i] = false;
        } else {
            ans[i] = true;
        }
    }

    for (int i : ans) {
        if (i) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
