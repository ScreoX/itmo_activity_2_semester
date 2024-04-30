#include "iostream"
#include "queue"
#include "vector"

using namespace std;
const int N = 1505;
vector<pair<int, int>> tu[N];
int w[N];
int vis[N];

struct T {
    long long num, p;
    int i, j;

    bool operator<(const T &t) const &{
        if (num != t.num) {
            return num > t.num;
        }
        return p < t.p;
    }
};

T dp[N][N];

void dfs(int now) {
    if (vis[now])
        return;
    vis[now] = 1;
    for (auto [u, v]: tu[now])dfs(u);
}

void solve() {
    int n, m, p;
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++) {
        cin >> w[i], tu[i].clear(), vis[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)dp[i][j].num = 1e18;
    }
    for (int i = 1; i <= m; i++) {
        int u, v, s;
        cin >> u >> v >> s;
        tu[u].emplace_back(v, s);
    }
    dfs(1);
    if (!vis[n]) {
        cout << "-1\n";
        return;
    }

    priority_queue<T> Q;
    Q.push({0, p, 1, 1});
    dp[1][1] = {0, p};
    while (!Q.empty()) {
        T now = Q.top();
        Q.pop();
        long long num = now.num;
        p = now.p;
        int i = now.i, j = now.j;
        if (i == n) {
            cout << num << '\n';
            return;
        }
        for (auto [v, s]: tu[i]) {
            int ma = j;
            if (w[v] >= w[j])
                ma = v;
            T nv;
            if (s > p) {
                long long t = s - p;
                long long nn = (t - 1) / w[j] + 1;
                nv = {num + nn, nn * w[j] - t, v, ma};
            } else nv = {num, p - s, v, ma};
            if (dp[v][ma] < nv) {
                dp[v][ma] = nv;
                Q.push(nv);
            }
        }
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);
    solve();
}
