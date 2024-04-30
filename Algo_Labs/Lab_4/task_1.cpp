#include <iostream>
#include <vector>

using namespace std;

bool kuns_algo(int i, std::vector<bool>& v, std::vector<std::vector<int>> &vec, std::vector<int> &matching) {
    if (v[i]) {
        return false;
    }

    v[i] = true;

    for (int to: vec[i]) {
        if (matching[to] == -1 || kuns_algo(matching[to], v, vec, matching)) {
            matching[to] = i;
            return true;
        }
    }

    return false;
}

int find_matchings(int vertexes_left, int vertexes_right, int size_of_match, vector<vector<int>> &ex_vec) {
    int res = 0;
    std::vector<int> matching(size_of_match, -1);
    for (int i = 0; i < ex_vec.size(); i++) {
        vector<bool> v(vertexes_left * vertexes_right + 1, false);
        if (kuns_algo(i, v, ex_vec, matching)) {
            res += 2;
        }
    }
    return res;
}

int main() {
    int n, m;
    cin >> n >> m;
    int q;
    cin >> q;

    vector<vector<int>> graph(n, vector<int>(m));

    int l = 0, r = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((i + j) % 2 == 0) {
                graph[i][j] = r++;
            } else {
                graph[i][j] = l++;
            }
        }
    }

    int x, y;
    for (int i = 0; i < q; i++) {
        cin >> x >> y;
        graph[x - 1][y - 1] = INT_MAX;
    }

    vector<vector<int>> extra_vector(l);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (graph[i][j] != INT_MAX && (i + j) % 2 == 1) {
                int v = graph[i][j];
                if (i > 0 && graph[i - 1][j] != INT_MAX) {
                    extra_vector[v].push_back(graph[i - 1][j]);
                }
                if (i < n - 1 && graph[i + 1][j] != INT_MAX) {
                    extra_vector[v].push_back(graph[i + 1][j]);
                }
                if (j > 0 && graph[i][j - 1] != INT_MAX) {
                    extra_vector[v].push_back(graph[i][j - 1]);
                }
                if (j < m - 1 && graph[i][j + 1] != INT_MAX) {
                    extra_vector[v].push_back(graph[i][j + 1]);
                }
            }
        }
    }

    int res = find_matchings(n, m, r, extra_vector);
    cout << res;

    return 0;
}
