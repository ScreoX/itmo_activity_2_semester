#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int a, b, weight;
};
int INF = 1000000000;
int find_cycle(vector<int>& prev, int last_vertex) {
    int res = 0;
    for (int i = last_vertex; ; i = prev[i]) {
        ++res;
        if (i == last_vertex && res > 1) {
            break;
        }
    }
    return res;
}

int find_last_prev(int cycle, int n, vector<int>& prev) {

    for (int i = 0; i < n; i++) {
        cycle = prev[cycle];
    }

    return cycle;
}

int BellmanFord(vector<Edge>& edges, int n, int m, int start) {
    vector<int> distance(n, INF);
    vector<int> previous(n, -1);

    distance[start] = 0;

    bool check = false;
    int cycle;

    for (int i = 0; i < n; ++i) {
        cycle = -1;
        for (int j = 0; j < m; ++j) {
            if (distance[edges[j].b] > distance[edges[j].a] + edges[j].weight) {
                distance[edges[j].b] = max(-INF, distance[edges[j].a] + edges[j].weight);
                previous[edges[j].b] = edges[j].a;
                check = true;
                cycle = edges[j].b;
            }
        }
        if (!check) {
            break;
        }
    }

    if (cycle == -1) {
        return -1;
    }

    int last_el = find_last_prev(cycle, n, previous);

    return find_cycle(previous, last_el);

}

int main() {

    int N, k;
    cin >> N >> k;

    for (int i = 0; i < N; i++) {
        int n, m, x, y, weight;
        cin >> n >> m;
        vector<Edge> edges(m);

        for (int j = 0; j < m; j++) {
            cin >> x >> y >> weight;
            Edge New_Edge = {x - 1, y - 1, weight};
            edges[j] = New_Edge;
        }

        int ans = BellmanFord(edges, n, m, 0);

        if (ans == -1 || ans <= k) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
