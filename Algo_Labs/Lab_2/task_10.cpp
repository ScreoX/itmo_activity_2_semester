#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct String {
    char commmand;
    int first;
    int second;
};

struct DSU {
    int* parent;
    int* rank;
    vector<set<int>> substracts;


    DSU(int n) {
        substracts.resize(n);
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            substracts[i].insert(i);
            rank[i] = 1;
        }
    }

    ~DSU() {
        delete[] parent;
        delete[] rank;
    }

    int findSet(int v) {
        if (v == parent[v]) {
            return v;
        }
        return parent[v] = findSet(parent[v]);
    }

    void unionSets(int a, int b) {
        a = findSet(a);
        b = findSet(b);

        if (a != b) {
            if (rank[a] > rank[b]) {
                swap(a, b);
            }

            rank[b] += rank[a];
            parent[a] = b;

            for (int i: substracts[a]) {
                substracts[b].insert(i);
            }
        }
    }
};

int main() {

    int n, m, q;
    std::cin >> n >> m >> q;

    int a, b;
    set<pair<int,int>> input;
    for (int i = 0; i < m; i++) {
        std::cin >> a >> b;
        input.insert({min(a - 1, b - 1), max(a - 1, b - 1)});
    }


    char command;
    String commands[q];
    for (int i = 0; i < q; i++) {
        std::cin >> command >> a >> b;
        if (command == '-') {
            input.erase({min(a - 1, b - 1), max(a - 1, b - 1)});
        }
        commands[i] = {command, min(a - 1, b - 1), max(a - 1, b - 1)};
    }

    DSU sub(n);

    for (auto i : input) {
        sub.unionSets(i.first, i.second);
    }

    vector<bool> ans;
    for (int i = q - 1; i >= 0; i--) {
        if (commands[i].commmand == '?') {
            if (commands[i].first == commands[i].second) {
                ans.push_back(true);
            } else {
                if (sub.findSet(commands[i].first) == sub.findSet(commands[i].second)) {
                    ans.push_back(true);
                } else {
                    ans.push_back(false);
                }
            }
        } else if (commands[i].commmand == '-') {
            if (commands[i].first != commands[i].second) {
                sub.unionSets(commands[i].first, commands[i].second);
            }
        }
    }

    for (int i = ans.size() - 1; i >= 0; i--) {
        if (ans[i]) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
    return 0;
}

