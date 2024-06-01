#include <iostream>
#include <vector>

using namespace std;

long long size_for_hash = 1000001;

long long doHash1(string &title) {
    long long x = 0;
    for (char ch : title) {
        x = (x * 221 + ch) % size_for_hash;
    }
    return x;
}

long long doHash2(string &title) {
    long long x = 0;
    for (char ch : title) {
        x = (x * 97 + ch) % size_for_hash;
    }
    return (x + 12345) % size_for_hash;
}

bool addElement(string &elem, vector<pair<string, long long>> &hashTable, long long studentNum) {

    string current = elem;

    long long pos = doHash1(current);
    long long lastPos = -1;
    long long count = 0;

    long long iterLimit = 9;

    while (count < iterLimit) {

        ++count;

        if (hashTable[pos].first.empty()) {
            hashTable[pos] = {current, studentNum};
            return true;
        }

        if (hashTable[pos].first == current) {
            hashTable[pos].second += studentNum;
            return true;
        }

        if (lastPos == pos) {
            break;
        }

        swap(current, hashTable[pos].first);
        swap(studentNum, hashTable[pos].second);

        lastPos = pos;

        if (pos == doHash1(current)) {
            pos = doHash2(current);
        } else {
            pos = doHash1(current);
        }
    }

    return false;
}

int main() {

    long long n;
    cin >> n;

    vector<pair<string, long long>> hashTable(size_for_hash);

    long long sum1 = 0, sum2 = 0, sum3 = 0;
    string title;

    for (long long i = 0; i < n; i++) {
        cin >> title;
        addElement(title, hashTable, 1);
    }
    for (long long i = 0; i < n; i++) {
        cin >> title;
        addElement(title, hashTable, 2);
    }
    for (long long i = 0; i < n; i++) {
        cin >> title;
        addElement(title, hashTable, 4);
    }

    for (auto &entry : hashTable) {
        if (!entry.first.empty()) {
            long long check = entry.second;
            if (check == 1) {
                sum1 += 3;
            } else if (check == 2) {
                sum2 += 3;
            } else if (check == 4) {
                sum3 += 3;
            } else if (check == 3) {
                sum1 += 1;
                sum2 += 1;
            } else if (check == 5) {
                sum1 += 1;
                sum3 += 1;
            } else if (check == 6) {
                sum2 += 1;
                sum3 += 1;
            }
        }
    }

    cout << sum1 << " " << sum2 << " " << sum3;

    return 0;
}
