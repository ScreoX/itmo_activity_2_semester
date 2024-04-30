#include <iostream>
#include <vector>
#include "queue"

void dijkstra(std::vector<std::vector<std::pair<int, int>>>& graph, int start, std::vector<int>& distance) {
    int vertices = graph.size();
    distance.assign(vertices, INT_MAX);

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> heap;

    distance[start] = 0;
    heap.push({0, start});

    while (!heap.empty()) {
        int i = heap.top().second;
        heap.pop();

        for (std::pair<int,int> edge : graph[i]) {
            int v = edge.first;
            int weight = edge.second;

            if (distance[i] != INT_MAX && distance[i] + weight < distance[v]) {
                distance[v] = distance[i] + weight;
                heap.push({distance[v], v});
            }
        }
    }
}

int main() {

    int n,m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int,int>>> graph(n);
    std::vector<int> distance(n, INT_MAX);
    int a, b, t;
    for (int i = 0; i < m; i++) {
        std::cin >> a >> b >> t;
        graph[a - 1].push_back({b - 1, t});
    }

    dijkstra(graph, 0, distance);

    if (distance[n - 1] != INT_MAX) {
        std::cout << distance[n - 1] << '\n';
    } else {
        std::cout << -1 << '\n';
    }
    return 0;
}