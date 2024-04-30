#include <iostream>
#include <vector>
#include <set>
#include <iterator>

using namespace std;

struct DSU {
    int* parent;
    int* rank;
    vector<set<int>::iterator> iters;
    vector<set<int>> substracts;


    DSU(int n) {
        substracts.resize(n);
        iters.resize(n);
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            substracts[i].insert(i);
            iters[i] = substracts[i].begin();
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

            int size;
            for (int i: substracts[a]) {
                size = substracts[b].size();
                substracts[b].insert(i);
                if (size % 2 == 0 && i > *iters[b]) {
                    iters[b]++;
                } else if (size % 2 != 0 && i < *iters[b]) {
                    iters[b]--;
                }
            }
        }
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;

    DSU dsu(n);
    int type, x, y;
    for (int i = 0; i < q; ++i) {
        cin >> type;

        if (type == 1) {
            cin >> x >> y;
            dsu.unionSets(x - 1, y - 1);
        } else {
            cin >> x;

            std::cout << *dsu.iters[dsu.findSet(x - 1)] + 1 << '\n';
        }
    }
    return 0;
}

