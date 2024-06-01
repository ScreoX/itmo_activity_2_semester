#include <iostream>
#include <vector>

using namespace std;

void prefixFunc(string& s) {

    size_t size = s.size();

    vector<int> prefix(size, 0);

    for (int i = 1; i < size; ++i) {
        int temp = prefix[i - 1];
        while (temp > 0 && s[i] != s[temp]) {
            temp = prefix[temp - 1];
        }
        if (s[i] == s[temp]) {
            temp++;
        }
        prefix[i] = temp;
    }

    for (int i : prefix) {
        cout << i << " ";
    }

}

int main() {

    string input;
    cin >> input;

    prefixFunc(input);

    return 0;
}
