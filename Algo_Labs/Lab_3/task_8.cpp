#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void dijkstra(std::vector<std::vector<long long>> &graph, long long start, std::vector<long long> &distance) {

    std::priority_queue<std::pair<long long, long long>, std::vector<std::pair<long long, long long>>, std::greater<std::pair<long long, long long>>> heap;

    distance[start] = 0;
    heap.push({0, start});

    while (!heap.empty()) {
        long long u = heap.top().second;
        heap.pop();

        for (long long v = 0; v < graph.size(); ++v) {
            if (graph[u][v] != LONG_LONG_MAX) {
                long long weight = graph[u][v];

                if (distance[u] != LONG_LONG_MAX && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    heap.push({distance[v], v});
                }
            }
        }
    }
}


int main() {

    long long n, m, k;
    cin >> n >> m >> k;

    vector<vector<long long>> graph(n, vector<long long>(n, LONG_LONG_MAX));

    long long s, t, x;
    for (long long i = 0; i < m; i++) {
        cin >> s >> t;
        vector<int> input(s);
        for (long long j = 0; j < input.size(); j++) {
            cin >> x;
            input[j] = x - 1;
        }
        for (long long j = 0; j < input.size() - 1; j++) {
            for (long long l = j + 1; l < input.size(); l++) {
                graph[input[j]][input[l]] = min(t, graph[input[j]][input[l]]);
                graph[input[l]][input[j]] = min(t, graph[input[l]][input[j]]);
            }
        }
    }

    std::vector<long long> distance(n, LONG_LONG_MAX);

    for (long long i = 0; i < n; ++i) {
        graph[i][i] = 0;
    }

    dijkstra(graph, 0, distance);

    if (distance[k - 1] != LONG_LONG_MAX) {
        std::cout << distance[k - 1];
    } else {
        std::cout << -1;
    }

    return 0;
}
