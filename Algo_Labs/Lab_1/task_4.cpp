#include <iostream>
#include <vector>
#include "set"

std::vector<int> order;
int SSC_count = 0;

void dfs1(std::vector<int>& v, std::vector<std::vector<int>>& g, int ind) {
    v[ind] = 1;

    for (int j : g[ind]) {
        if (!v[j]) {
            dfs1(v, g, j);
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

std::set<std::pair<int, int>> complete_set(std::vector<std::vector<int>>& g, std::vector<int>& v) {
    std::set<std::pair<int,int>> NewSet;

    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g[i].size(); j++) {
            if (v[i] != v[g[i][j]]) {
                NewSet.insert({v[i] - 1, v[g[i][j]] - 1});
            }
        }
    }

    return NewSet;
}
int main() {

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph(n);
    std::vector<std::vector<int>> reversed_graph(n);
    std::vector<int> visited(n, 0);
    order.resize(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        reversed_graph[b - 1].push_back(a - 1);
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs1(visited, reversed_graph, i);
        }
    }

    visited.assign(n, 0);

    for (int i = order.size() - 1; i > 0; i--) {
        if (!visited[order[i]]) {
            dfs2(visited, graph, order[i], ++SSC_count);
        }
    }

    std::set<std::pair<int, int>> s = complete_set(graph, visited);
    int count_roads = s.size();

    std::vector<int> NumOfFamily(SSC_count, INT_MAX);

    for (int i = 0; i < visited.size(); i++) {
        NumOfFamily[visited[i] - 1] = std::min(NumOfFamily[visited[i] - 1], i);
    }

//    std::vector<std::pair<int, int>> ans(SSC_count);
//    for (std::pair<int, int> iter: s) {
//
//        std::pair<int, int> p = iter;
//
//        ans.push_back({NumOfFamily[p.first] + 1, NumOfFamily[p.second] + 1});
//
//    }
    std::set<std::pair<int, int>> answer;
    if (count_roads != 0) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < graph[i].size(); j++) {
                if (visited[i] != visited[graph[i][j]]) {
                    std::pair<int, int> p;
                    p.first = NumOfFamily[visited[i] - 1] + 1;
                    p.second = NumOfFamily[visited[graph[i][j]] - 1] + 1;
                    answer.insert(p);
                }
            }
        }
    }
    std::cout << NumOfFamily.size() << " " << count_roads << '\n';

    if (count_roads != 0) {
        for (auto i: answer) {
            std::cout << i.first << " " << i.second << "\n";
        }
    }


    return 0;
}
