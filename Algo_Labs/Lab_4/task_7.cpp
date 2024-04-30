#include <iostream>
#include <vector>
#include "set"
#include <algorithm>

using namespace std;

vector<int> find_ham_cycle(vector<int>& order, set<pair<int, int>>& edges, int n) {

    for (int k = 0; k < n * (n - 1); ++k) {
        if (edges.find({order[0], order[1]}) == edges.end() && edges.find({order[1], order[0]}) == edges.end()) {
            int i = 2;
            while (i < order.size() - 1 && (edges.find({order[0], order[i]}) == edges.end() || edges.find({order[1], order[i + 1]}) == edges.end())) {
                ++i;
            }
            reverse(order.begin() + 1, order.begin() + i + 1);
        }
        order.push_back(order.front());
        order.erase(order.begin());
    }
    return order;
}

int main() {
    int n, m;
    cin >> n >> m;
    set<pair<int, int>> edges;
    vector<int> input_v;
    vector<bool>check(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if (!check[a]) {
            input_v.push_back(a);
            check[a] = true;
        }
        if (!check[b]) {
            input_v.push_back(b);
            check[b] = true;
        }
        edges.insert({a, b});
    }

    vector<int> result = find_ham_cycle(input_v, edges, n);
    for (int v : result) {
        cout << v << " ";
    }
    return 0;
}
