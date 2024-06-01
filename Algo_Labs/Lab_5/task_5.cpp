#include "blazingio.hpp"
#include <vector>

using namespace std;

int doHash(int elem, int size) {
    return (elem + 123421267) % size;
}

int findFactorial(int el) {
    if (el == 0 || el == 1) {
        return 1;
    }
    int res = 1;
    while (el != 0) {
        res *= (el--);
    }
    return res;
}

int main() {
    int n;
    cin >> n;

    int size = 4 * n;

    vector<vector<int>> hashTable(size);

    int x;

    for (int distance = 0; distance < n; distance++) {
        cin >> x;
        hashTable[doHash(x - distance, size)].push_back(x);
    }

    int ans = 0;

    for (auto & i : hashTable) {
        int elem;

        if (i.size() <= 2) {
            elem = 2 - i.size();
        } else {
            elem = i.size() - 2;
        }

        ans += (findFactorial(i.size()) / (2 * findFactorial(elem)));
    }

    cout << ans;

    return 0;
}