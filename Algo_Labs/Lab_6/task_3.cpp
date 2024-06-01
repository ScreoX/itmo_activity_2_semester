#include <iostream>

using namespace std;

bool checkEqual(string &song, int start_first, int start_second, int len, int sizeString) {

    string firstSubstring, secondSubstring;

    for (int i = start_first; (i < start_first + len) && (i < sizeString); i++) {
        firstSubstring.push_back(song[i]);
    }

    for (int i = start_second; (i < start_second + len) && (i < sizeString); i++) {
        secondSubstring.push_back(song[i]);
    }

    if (firstSubstring == secondSubstring) {
        return true;
    }

    return false;

}

int main() {
    int n, m;

    cin >> n >> m;

    string input_string;
    cin >> input_string;

    int res = 0;

    int input_i, input_j, input_k;

    for (int i = 0; i < m; i++) {
        cin >> input_i >> input_j >> input_k;
        input_i--;
        input_j--;
        if (checkEqual(input_string, input_i, input_j, input_k, n)) {
            res++;
        }
    }

    cout << res;

    return 0;
}