#include <iostream>
#include <vector>

unsigned long long inf = LONG_LONG_MAX + LONG_LONG_MAX - 2;

unsigned long long find_optimal_vertex(std::vector<std::vector<unsigned long long>>& dist) {
    unsigned long long min_dist = inf + 1;
    long long res = -1;

    for (long long i = 0; i < dist.size(); ++i) {
        unsigned long long temp_dist = 0;

        for (long long j = 0; j < dist.size(); ++j) {
            if (i != j) {
                temp_dist += dist[i][j];
            }
        }
        if (temp_dist < min_dist) {
            min_dist = temp_dist;
            res = i;
        }
    }

    return res + 1;
}

int main() {
    unsigned long long n, m;
    std::cin >> n >> m;
    std::vector<std::vector<unsigned long long>> graph(n, std::vector<unsigned long long>(n, inf));

    unsigned long long a, b;
    unsigned long long t;
    for (unsigned long long i = 0; i < n; i++) {

        graph[i][i] = 0;

    }
    for (unsigned long long i = 0; i < m; i++) {

        std::cin >> a >> b >> t;
        a--;
        b--;
        graph[a][b] = std::min(t, graph[a][b]);
        graph[b][a] = std::min(t,graph[b][a]);

    }

    for (unsigned long long k = 0; k < graph.size(); ++k) {
        for (unsigned long long i = 0; i < graph.size(); ++i) {
            for (unsigned long long j = 0; j < graph.size(); ++j) {
                if (graph[i][k] != inf && graph[k][j] != inf) {
                    graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }
    }

    unsigned long long res = find_optimal_vertex(graph);

    std::cout << res;

    return 0;
}

