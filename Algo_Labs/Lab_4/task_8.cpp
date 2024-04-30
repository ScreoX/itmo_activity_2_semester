#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1e5 + 1;
vector <pair <int, int>> g[N], vec;
int n, L, W, sz[N], fen[N];
bool mark[N];
long long ans = 0;

void dfs_sz(int v, int par = -1) {
    sz[v] = 1;
    for (auto u : g[v]) {
        if (!mark[u.first] && u.first - par) {
            dfs_sz(u.first, v), sz[v] += sz[u.first];
        }
    }
}

void add(int i, int sign) {
    for (i++; i < N; i += i & -i) {
        fen[i] += sign;
    }
}

int get(int i) {
    int res = 0;
    for (i++; i; i -= i & -i) {
        res += fen[i];
    }
    return res;
}

void dfs(int v, int par, int len, int weight) {
    vec.emplace_back(weight, len);
    for (auto u : g[v]) {
        if (u.first - par && !mark[u.first]) {
            dfs(u.first, v, len + 1, weight + u.second);
        }
    }
}

void count(int v, int sign, int len, int weight) {
    vec.clear();
    dfs(v, -1, len, weight);
    sort(vec.begin(), vec.end());
    for (int i = vec.size() - 1, j = -1; i > -1; i--) {
        while (j + 1 < i && vec[j + 1].first + vec[i].first <= W) {
            add(vec[++j].second, 1);
        }
        if (j == i) {
            add(vec[j--].second, -1);
        }
        ans += 1LL * sign * get(max(L - vec[i].second, -1));
    }
}

void solve(int v) {
    count(v, 1, 0, 0);
    mark[v] = true;
    for (auto u : g[v]) {
        if (!mark[u.first]) {
            count(u.first, -1, 1, u.second);
        }
    }
}

int find(int v) {
    dfs_sz(v);
    bool check = false;
    int par = -1;
    n = sz[v];
    while (!check) {
        check = true;
        for (auto u : g[v]) {
            if (!mark[u.first] && u.first - par && sz[u.first] > n / 2) {
                check = false;
                par = v;
                v = u.first;
                break;
            }
        }
    }
    return v;
}

void divide(int v) {
    v = find(v);
    solve(v);
    for (auto u : g[v]) {
        if (!mark[u.first]) {
            divide(u.first);
        }
    }
}

int main() {
    cin >> n >> L >> W;
    int p, w;
    for (int i = 1; i < n; i++) {
        cin >> p >> w;
        g[i].emplace_back(p - 1, w);
        g[p - 1].emplace_back(i, w);
    }
    divide(0);

    cout << ans;
    return 0;
}
