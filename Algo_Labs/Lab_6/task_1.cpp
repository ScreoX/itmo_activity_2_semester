#include <iostream>
#include <vector>

using namespace std;

vector<int> zFunc(string& stringConcatenation) {

    int size = stringConcatenation.size();

    vector<int> z_func_vector(size);
    int left = 0, right = 0;
    for (int i = 1; i < size; ++i) {
        z_func_vector[i] = max(0, min(right - i, z_func_vector[i - left]));
        while (i + z_func_vector[i] < size && stringConcatenation[z_func_vector[i]] == stringConcatenation[i + z_func_vector[i]]) {
            z_func_vector[i]++;
        }
        if (i + z_func_vector[i] > right) {
            left = i;
            right = i + z_func_vector[i];
        }
    }
    return z_func_vector;
}

void findSubstring(string& gimn, string& substring) {
    string stringConcatenation = substring + '*' + gimn;

    vector<int> z_func_vector = zFunc(stringConcatenation);

    vector<int> ansIndices;

    size_t m = substring.size();
    size_t n = stringConcatenation.size();

    for (size_t i = m + 1; i < n; i++) {
        if (z_func_vector[i] == m) {
            ansIndices.push_back(i - m - 1);
        }
    }

    cout << ansIndices.size() << '\n';

    for (int iter : ansIndices) {
        cout << iter << " ";
    }

}

int main() {

    string gimn, substring;
    cin >> gimn >> substring;

    findSubstring(gimn, substring);

    return 0;
}
