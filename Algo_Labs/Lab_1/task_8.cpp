#include <iostream>
#include <vector>
#include "string"

void dfs1(std::vector<int>& v, std::vector<std::vector<int>>& g, int ind, std::vector<int>& order) {
    v[ind] = 1;

    for (int j : g[ind]) {
        if (!v[j]) {
            dfs1(v, g, j, order);
        }
    }
    order.push_back(ind);
}

void dfs2(std::vector<int>& v, std::vector<std::vector<int>>& g, int ind, int component) {
    v[ind] = component;

    for (int j : g[ind]) {
        if (!v[j]) {
            dfs2(v, g, j, component);
        }
    }
}

int main() {
    int n, k;
    std::cin >> n >> k;

    int size = 2 * n;
    std::vector<std::vector<int>> graph(size);
    std::vector<std::vector<int>> reversed_graph(size);
    std::vector<int> visited(size);
//    std::vector<int> components(size, -1);
    std::vector<int> order(size);

    std::string s, new_str;
    int y;
    for (int i = 0; i < k; i++) {
        std::cin >> s;
        if (s[0] == '!') {
            // !1: (1 -> !1) - correct
            int d = 1;
            int num = 0;
            for (auto j = s.length() - 1; j > 0; j--) {
                num += (s[j] - 48) * d;
                d *= 10;
            }
            graph[num * 2 - 2].push_back(num * 2 - 1);

            reversed_graph[num * 2 - 1].push_back(num * 2 - 2);
        } else {
            int num = std::stoi(s);
            std::cin >> new_str >> y;
            if (new_str[0] == '^') {
                // 1 ^ 2: (1 || 2)(!1 || !2) : (!1 -> 2)(!2 -> 1)(1 -> !2)(2 -> !1) - correct
                graph[num * 2 - 1].push_back(y * 2 - 2);
                graph[y * 2 - 1].push_back(num * 2 - 2);
                graph[num * 2 - 2].push_back(y * 2 - 1);
                graph[y * 2 - 2].push_back(num * 2 - 1);

                reversed_graph[y * 2 - 2].push_back(num * 2 - 1);
                reversed_graph[num * 2 - 2].push_back(y * 2 - 1);
                reversed_graph[y * 2 - 1].push_back(num * 2 - 2);
                reversed_graph[num * 2 - 1].push_back(y * 2 - 2);
            } else if (new_str[0] == '-') {
                // 1 -> 2: (1 -> 2)(!2 -> !1) - correct
                graph[2 * num - 2].push_back(2 * y - 2);
                graph[2 * y - 1].push_back(2 * num - 1);

                reversed_graph[2 * y - 2].push_back(2 * num - 2);
                reversed_graph[2 * num - 1].push_back(2 * y - 1);
            } else if (new_str[0] == '&') {
                // 1 & 2: (!1 -> 1)(!2 -> 2) - correct
                graph[num * 2 - 1].push_back(num * 2 - 2);
                graph[y * 2 - 1].push_back(y * 2 - 2);

                reversed_graph[num * 2 - 2].push_back(num * 2 - 1);
                reversed_graph[y * 2 - 2].push_back(y * 2 - 1);
            } else if (new_str[0] == '|') {
                // 1 || 2: (!1 -> 2)(!2 -> 1) - correct
                graph[num * 2 - 1].push_back(y * 2 - 2);
                graph[y * 2 - 1].push_back(num * 2 - 2);

                reversed_graph[y * 2 - 2].push_back(num * 2 - 1);
                reversed_graph[num * 2 - 2].push_back(y * 2 - 1);
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        if (!visited[i]) {
            dfs1(visited, reversed_graph, i, order);
        }
    }

    visited.assign(size, 0);
    int SSC_count = 0;

    for (int i = order.size() - 1; i > 0; i--) {
        if (!visited[order[i]]) {
            dfs2(visited, graph, order[i], ++SSC_count);
        }
    }

    for (int i = 0; i < size; ++i) {
        if (visited[i] == visited[i ^ 1]) {
            std::cout << "NO";
            return 0;
        }
    }
    std::cout << "YES";

    return 0;
}
