#include <iostream>
#include <vector>
#include "algorithm"
#include "queue"


struct Edge {
    int low;
    int up;
    Edge(int x, int y) {
        this->low = x;
        this->up = y;
    }
};
void bfs(int ind, int l, int r, std::vector<std::vector<std::pair<int, Edge>>>& g, std::vector<bool>& visited) {

    visited[ind] = true;
    std::queue<int> q;
    q.push(ind);

    while (!q.empty()) {
        int i = q.front();
        q.pop();
        for (std::pair<int, Edge> u : g[i]) {
            if (!visited[u.first] && l >= u.second.low && r <= u.second.up) {
                visited[u.first] = true;
                q.push(u.first);
            }
        }
    }
}

bool check(int left, int mid, std::vector<bool>& visited, std::vector<std::vector<std::pair<int, Edge>>>& g) {
    visited.assign(visited.size(), false);
    bfs(0, left, mid, g, visited);
    if (visited[visited.size() - 1]) {
        return true;
    }
    return false;
}


int binary_search(int l, int r, std::vector<bool>& visited, std::vector<std::vector<std::pair<int, Edge>>>& g) {
    int start_l = l;
    ++r;
    int result = -1;
    while (r - l > 1) {
        int m = (r + l) / 2;
        if (check(start_l, m, visited, g)) {
            result = m;
            l = m;
        } else {
            r = m;
        }
    }
    return result;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph_edges(m, std::vector<int>(4));
    std::vector<int> m_left;
    std::vector<bool> visited(n, false);

    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;

        graph_edges[i][0] = a - 1;
        graph_edges[i][1] = b - 1;
    }

    int l, r;
    int mx_r = -1;
    for (int i = 0; i < m; i++) {

        std::cin >> l >> r;

        graph_edges[i][2] = l;
        graph_edges[i][3] = r;

        m_left.push_back(l);
        mx_r = std::max(r, mx_r);
    }

    std::vector<std::vector<std::pair<int, Edge>>> graph(n);
    for (int i = 0; i < graph_edges.size(); i++) {
        Edge x = Edge(graph_edges[i][2], graph_edges[i][3]);
        std::pair<int, Edge> a(graph_edges[i][1], x);
        std::pair<int, Edge> b(graph_edges[i][0], x);
        graph[graph_edges[i][1]].push_back(b);
        graph[graph_edges[i][0]].push_back(a);
    }

    int result = -1;
    for (int i: m_left) {
        int right = binary_search(i, mx_r, visited, graph);
        result = std::max(result, right - i + 1);
    }

    std::cout << result;

    return 0;
}

/*

4 4
1 2
1 3
2 4
3 4
1 4
1 4
3 4
1 4

4

6 7
1 2
2 4
4 6
1 3
3 5
5 6
2 5
40 50
90 100
1 100
9 20
6 12
1 111
41 49

9

2 1
1 2
1 1000000

1000000

6 7
1 4
1 2
1 5
4 3
2 3
3 5
3 6
2 8
1 13
1235 1250
9 15
11 13
1000 2000
8 15

3

3 10
2 1
1 2
2 1
1 2
2 1
3 2
2 3
3 2
2 3
2 3
1 10
3 100
13 14
100 1000
1 1
2 8
6 13
1 15
200 300
1 16

101

6 10
1 2
1 3
1 4
1 5
1 6
2 3
3 4
4 5
5 6
2 6
1 10
1 8
1 6
1 4
1 2
1 20
1 30
1 40
1 50
1 20

10

7 6
1 2
2 7
1 3
3 4
4 5
5 2
1 3
1 4
1 4
1 4
1 4
1 4

4


4 4
1 2
1 3
2 4
3 4
999999 1000000
20 40
20 40
999999 1000000

-1

 */