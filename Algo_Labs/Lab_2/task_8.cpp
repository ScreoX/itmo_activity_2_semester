#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;

size_t do_hash(int f, int s, int n) {
    return (n * hash<int>{}(f) ^ hash<int>{}(s));
}

vector<int> enter, ret;
int t = 0;
int res = 0;

void dfs_bridges(int i, int p, vector<bool> &visited, vector<vector<int>> &graph, set<pair<int, int>> &ans, unordered_map<size_t , bool> &check, int n) {
    visited[i] = true;
    enter[i] = ret[i] = t;
    ++t;
    for (int j : graph[i]) {
        if (j == p) {
            continue;
        }
        if (visited[j]) {
            enter[i] = min(enter[i], ret[j]);
        } else {
            dfs_bridges(j, i, visited, graph, ans, check, n);
            enter[i] = min(enter[i], enter[j]);
            if (enter[j] > ret[i] && (check[do_hash(j, i, n)] && check[do_hash(i, j, n)]) == 0) {
                ans.insert({i , j});
                ans.insert({j , i});
            }
        }
    }
}

void condensation(int i, int p, int color, vector<vector<int>> &graph, vector<bool> &visited, vector<int> &cmp, vector<int> &count_cmp) {
    visited[i] = true;
    cmp[i] = color;
    count_cmp[cmp[i]]++;
    for (int j : graph[i]) {
        if (!visited[j] && j != p) {
            condensation(j, i, color, graph, visited, cmp, count_cmp);
        }
    }
}

void find_paths(int i, int from, vector<vector<int>> &graph, vector<bool> &visited, vector<int> &distance, vector<int> &cmp, vector<int> &count_cmp) {
    visited[i] = true;
    for (int j : graph[i]) {
        if (j == from) {
            continue;
        }
        if (!visited[j] && j != from) {
            find_paths(j, i, graph, visited, distance, cmp, count_cmp);
        }
        distance[i] += distance[j];
    }
    res += distance[i] * (count_cmp[cmp[i]] - distance[i]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m; cin >> n >> m;

    vector<int> vertexes(n);
    for (int i = 0; i < n; i++) {
        vertexes[i] = i;
    }

    unordered_map<string, int> input_map;
    unordered_map<size_t, bool> check_added(n);
    unordered_map<size_t, bool> double_edges(n);

    enter.assign(n, 0);
    ret.assign(n, 0);
    vector<bool> visited(n, false);

    string x, y;
    for (int i = 0; i < n; i++) {
        cin >> x;
        input_map[x] = i;
    }

    vector<vector<int>> graph(n);

    for (int i = 0; i < m; ++i) {
        cin >> x >> y;

        size_t first = do_hash(input_map[x], input_map[y], n);
        size_t second = do_hash(input_map[y], input_map[x], n);

        if (!(double_edges[first] && double_edges[second])) {
            graph[input_map[x]].push_back(input_map[y]);
            graph[input_map[y]].push_back(input_map[x]);
            double_edges[first] = true;
            double_edges[second] = true;
        } else {
            check_added[first] = true;
            check_added[second] = true;
        }
    }

    set<pair<int, int>> ans;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs_bridges(i, -1, visited, graph, ans, check_added, n);
        }
    }

    vector<vector<int>> cond_graph(n);

    for (auto iter = ans.begin(); iter != ans.end(); iter++) {
        cond_graph[iter->first].push_back(iter->second);
    }

    vector<int> count_components(n, 0);
    visited.assign(n, false);
    vector<int> components(n, -1);

    int color = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && !cond_graph[i].empty()) {
            condensation(i, -1, color++, cond_graph, visited, components, count_components);
        }
    }

    visited.assign(n, false);
    vector<int> distance(n, 1);

    for (int i = 0; i < n; i++) {
        if (!visited[i] && !cond_graph[i].empty()) {
            find_paths(i, -1, cond_graph, visited, distance, components, count_components);
        }
    }

    cout << res;

    return 0;
}
