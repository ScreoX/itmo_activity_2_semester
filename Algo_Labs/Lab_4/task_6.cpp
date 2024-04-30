#include "iostream"
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    int to, cap, cost, flow;
    size_t rev;
};

pair<int, int> findMinCostMaxFlow(int n, int s, int t, vector<vector<Edge>> &graph) {
    int flow = 0, cost = 0;
    while (true) {
        vector<int> id(n, 0);
        vector<int> dist(n, 1e9);
        vector<int> parentEdge(n);
        vector<size_t> parent(n);

        queue<int> q;
        q.push(s);
        dist[s] = 0;
        vector<bool> inQueue(n, false);
        inQueue[s] = true;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            id[v] = 2;
            inQueue[v] = false;
            for (size_t i = 0; i < graph[v].size(); ++i) {
                Edge &r = graph[v][i];
                if (r.flow < r.cap && dist[v] + r.cost < dist[r.to]) {
                    dist[r.to] = dist[v] + r.cost;
                    if (!inQueue[r.to]) {
                        q.push(r.to);
                        inQueue[r.to] = true;
                    }
                    parent[r.to] = v;
                    parentEdge[r.to] = i;
                }
            }
        }

        if (dist[t] == 1e9) {
            break;
        }

        int pushFlow = 1e9;
        for (int v = t; v != s; v = parent[v]) {
            int pv = parent[v];
            size_t pr = parentEdge[v];
            pushFlow = min(pushFlow, graph[pv][pr].cap - graph[pv][pr].flow);
        }

        for (int v = t; v != s; v = parent[v]) {
            int pv = parent[v];
            size_t pr = parentEdge[v];
            size_t rev = graph[pv][pr].rev;
            graph[pv][pr].flow += pushFlow;
            graph[v][rev].flow -= pushFlow;
            cost += graph[pv][pr].cost * pushFlow;
        }
        flow += pushFlow;
    }

    return {flow, cost};
}

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<Edge>> graph(n);
    for (int i = 0; i < m; ++i) {
        int from, to, cap, cost;
        cin >> from >> to >> cap >> cost;
        --from; --to;

        size_t reverseIndexTo = graph[to].size();
        size_t reverseIndexFrom = graph[from].size();

        graph[from].emplace_back(to, cap, cost, 0, reverseIndexTo);
        graph[to].emplace_back(from, 0, -cost, 0, reverseIndexFrom);


    }

    pair<int, int> result = findMinCostMaxFlow(n, s - 1, t - 1, graph);

    cout << result.first << " " << result.second;

    return 0;
}
