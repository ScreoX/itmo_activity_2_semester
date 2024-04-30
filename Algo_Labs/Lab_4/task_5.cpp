#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Info {
    int x;
    vector<bool> left;
    vector<bool> right;
};

bool check(int x, vector<int>& right_part, vector<bool>& vis, const vector<vector<int>>& g) {
    if (vis[x]) {
        return false;
    }
    vis[x] = true;
    for (int y : g[x]) {
        if (right_part[y] == 0 || check(right_part[y], right_part, vis, g)) {
            right_part[y] = x;
            return true;
        }
    }
    return false;
}

void check_optimal(int x, vector<bool>& left, vector<bool>& right, const vector<vector<int>>& g, const vector<int>& right_part) {
    if (left[x]) return;
    left[x] = true;
    for (int y : g[x]) {
        if (right_part[y] && !right[y]) {
            right[y] = true;
            check_optimal(right_part[y], left, right, g, right_part);
        }
    }
}

int dfs(int n, vector<vector<int>>& g, vector<int>& right_part) {
    int ans = 0;
    vector<bool> vis(n + 1, false);
    for (int i = 1; i <= n; i++) {
        vis.assign(vis.size(), false);
        ans += check(i, right_part, vis, g);
    }
    return ans;
}
Info checkMinCountVertex(int n, int m, vector<vector<int>>& g) {
    vector<int> right_part(m + 1, 0);
    int ans = dfs(n, g, right_part);

    vector<bool> vis(n + 1, false);
    vector<bool> left(n + 1, false);
    vector<bool> right(m + 1, false);

    for (int i = 1; i <= m; i++) {
        if (right_part[i]) {
            vis[right_part[i]] = true;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            check_optimal(i, left, right, g, right_part);
        }
    }

    return {ans, left, right};
}

int main() {
    int N, K, M;
    cin >> N >> K >> M;
    vector<vector<int>> graph(N + 1);
    int x, y;
    for (int i = 0; i < M; i++) {
        cin >> x >> y;
        graph[x].push_back(y);
    }

    Info res = checkMinCountVertex(N, K, graph);

    vector<int> ans_for_left, ans_for_right;
    for (int i = 1; i <= N; i++) {
        if (!res.left[i]) {
            ans_for_left.push_back(i);
        }
    }
    for (int i = 1; i <= K; i++) {
        if (res.right[i]) {
            ans_for_right.push_back(i);
        }
    }
    cout << ans_for_left.size();
    if (ans_for_left.empty()) {
        cout << "\n";
    } else {
        cout << "\n";
        for (int i : ans_for_left) {
            cout << i << " ";
        }
    }

    cout << "\n" << ans_for_right.size();
    if (ans_for_right.empty()) {
        cout << "\n";
    } else {
        cout << '\n';
        for (int i : ans_for_right) {
            cout << i << " ";
        }
    }

    return 0;
}
