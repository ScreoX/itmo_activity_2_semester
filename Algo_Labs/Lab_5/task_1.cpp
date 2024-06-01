#include <iostream>
#include <vector>

using namespace std;

struct HashInfo {
    int first{};
    int second{};
    bool consist{};
};

int size_for_hash;

int doHash(int elem) {
    return (elem % size_for_hash);
}

void insertElement(vector<HashInfo> &hash_table, int element) {
    int newHash = doHash(element);
    while (hash_table[newHash].first != INT_MIN || !hash_table[newHash].consist) {
        if (hash_table[newHash].first == element) {
            break;
        }
        newHash = (newHash + 1) % 12345;
    }
    hash_table[newHash] = {element, hash_table[newHash].second + 1, true};
}

void deleteElementFromHashTable(vector<HashInfo> &hash_table, int x) {
    int newHash = doHash(x);
    while (hash_table[newHash].first != x) {
        if (hash_table[newHash].first == INT_MIN && hash_table[newHash].consist) {
            return;
        }
        newHash = (newHash + 1) % 12345;
    }
    hash_table[newHash] = {INT_MIN, 0, false};
}

int takeVal(vector<HashInfo> &hash_table, int element) {
    int newHash = doHash(element);
    while (hash_table[newHash].first != INT_MIN || !hash_table[newHash].consist) {
        if (hash_table[newHash].first == element) {
            return hash_table[newHash].second;
        }
        newHash = (newHash + 1) % 12345;
    }
    return -123;
}

void changeVal(vector<HashInfo> &hash_table, int element) {
    int newHash = doHash(element);
    while (hash_table[newHash].first != INT_MIN || !hash_table[newHash].consist) {
        if (hash_table[newHash].first == element) {
            break;
        }
        newHash = (newHash + 1) % size_for_hash;
    }
    hash_table[newHash] = {element, hash_table[newHash].second - 1, true};
}

bool check_contain(vector<HashInfo> &hash_table, int element) {
    int newHash = doHash(element);
    while (hash_table[newHash].first != INT_MIN || !hash_table[newHash].consist) {
        if (hash_table[newHash].first == element) {
            return false;
        }
        newHash = (newHash + 1) % size_for_hash;
    }
    return true;
}

int main() {
    int n;

    cin >> n;

    size_for_hash = n;

    vector<HashInfo> X_hash_table(n * 100);
    vector<HashInfo> Y_hash_table(n * 100);

    vector<HashInfo> input;

    int cnt = 0;
    for (int i = 0; i < n * 100; i++) {
        HashInfo prepare = {INT_MIN, 0, true};
        X_hash_table[i] = Y_hash_table[i] = prepare;
    }

    int first, second;

    for (int i = 0; i < n; i++) {
        cin >> first >> second;
        if (check_contain(X_hash_table, first) && check_contain(Y_hash_table, second)) {
            insertElement(X_hash_table, first);
            insertElement(Y_hash_table, second);

            input.push_back({first, second, true});
        }
    }
    for (auto i : input) {

        if (cnt > 3) break;

        first = i.first;
        second = i.second;

        if (takeVal(X_hash_table, first) == 1 && takeVal(Y_hash_table, second) == 1) {
            cnt++;
            deleteElementFromHashTable(X_hash_table, first);
            deleteElementFromHashTable(Y_hash_table, second);
        } else if (takeVal(X_hash_table, first) == 1 || takeVal(Y_hash_table, second) == 1) {
            if (takeVal(X_hash_table, first) != -123) {
                cnt++;
                deleteElementFromHashTable(X_hash_table, first);
                changeVal(Y_hash_table, second);
            } else {
                cnt++;
                deleteElementFromHashTable(Y_hash_table, second);
                changeVal(X_hash_table, first);
            }
        }
    }
    if (cnt == 3) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}

