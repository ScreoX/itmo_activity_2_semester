#include <iostream>
#include <vector>

using namespace std;

unsigned long long size_for_hash;

struct Node {
    unsigned long long data, tempMax, tempMin, size;
    bool check = false;
    Node* next = nullptr;

    Node(unsigned long long val, unsigned long long tempMX, unsigned long long tempMN, unsigned long long len) {
        data = val;
        tempMax = tempMX;
        tempMin = tempMN;
        size = len;
        check = false;
        next = nullptr;
    }
};

unsigned long long doHash(unsigned long long elem) {
    return elem % size_for_hash;
}

unsigned long long takeHash(unsigned long long hash) {
    hash = (hash ^ (hash >> 30)) * 123294813;
    hash = (hash ^ (hash >> 20)) * 1373918171;
    hash = hash ^ (hash >> 10);
    return hash;
}

void add(vector<Node*>& hashTable, unsigned long long data, unsigned long long tempMax, unsigned long long tempMin, unsigned long long size) {
    unsigned long long index = doHash(data);
    if (hashTable[index] != nullptr) {
        Node* NewNode = hashTable[index];
        while (NewNode->next != nullptr) {
            NewNode = NewNode->next;
        }
        NewNode->next = new Node(data, tempMax, tempMin, size);
    } else {
        hashTable[index] = new Node(data, tempMax, tempMin, size);
    }
}

bool checkCorrectNode(Node* NewNode, unsigned long long data, unsigned long long tempMax, unsigned long long tempMin, unsigned long long size) {
    if (NewNode->data == data && NewNode->size == size && NewNode->tempMax == tempMax && NewNode->tempMin == tempMin && !NewNode->check) {
        return true;
    }
    return false;
}

bool checkConsist(vector<Node*>& hashTable, unsigned long long data, unsigned long long tempMax, unsigned long long tempMin, unsigned long long size) {
    Node* NewNode = hashTable[doHash(data)];
    while (NewNode != nullptr) {
        if (checkCorrectNode(NewNode, data, tempMax, tempMin, size)) {
            NewNode->check = true;
            return true;
        } else {
            NewNode = NewNode->next;
        }
    }
    return false;
}


int  main() {

    unsigned long long n, m;
    size_for_hash = 9e6;

    cin >> n;

    vector<unsigned long long> first, second;

    unsigned long long x;

    for (unsigned long long i = 0; i < n; i++) {
        cin >> x;
        first.push_back(x);
    }

    cin >> m;

    for (unsigned long long i = 0; i < m; i++) {
        cin >> x;
        second.push_back(x);
    }

    if (first.empty() || second.empty()) {
        cout << 0;
        return 0;
    }

    vector<Node*> hashTable(size_for_hash, nullptr);

    unsigned long long result = 0;
    unsigned long long data, hash1, hash2, hash3;

    unsigned long long tempMax, tempMin;

    for (unsigned long long i = 0; i < n; i++) {

        hash1 = 17;
        hash2 = 31;
        hash3 = 13;
        tempMax = -1e9;
        tempMin = 1e9;

        for (unsigned long long j = i; j < n; j++) {

            tempMax = max(first[j], tempMax);
            tempMin = min(first[j], tempMin);

            unsigned long long val = takeHash(first[j]);

            hash1 ^= val;
            hash2 *= val;
            hash3 += val;

            data = hash1 ^ hash2 ^ hash3 >> tempMin ^ tempMax;
            add(hashTable, data, tempMax, tempMin, j - i + 1);
        }

    }
    for (unsigned long long i = 0; i < m; i++) {
        hash1 = 17;
        hash2 = 31;
        hash3 = 13;
        tempMax = -1e9;
        tempMin = 1e9;

        for (unsigned long long j = i; j < m; j++) {
            tempMax = max(tempMax, second[j]);
            tempMin = min(tempMin, second[j]);

            unsigned long long val = takeHash(second[j]);

            hash1 ^= val;
            hash2 *= val;
            hash3 += val;

            data = hash1 ^ hash2 ^ hash3 >> tempMin ^ tempMax;
            if (checkConsist(hashTable, data, tempMax, tempMin, j - i + 1)) {
                result = max(result, j - i + 1);
            }
        }
    }

    cout << result;


    return 0;
}

/*

3
1 1 2
5
3 2 2 2 1 4

*/