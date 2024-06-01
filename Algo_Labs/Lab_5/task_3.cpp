#include <iostream>

using namespace std;

int do_hash(int num, int size) {
    return ((num * 41 / 37 * num) + size * num % 7 * size * size * num) ;
}

int main() {

    int n;
    cin >> n;

    int x;

    long long check1 = 0, check2 = 0;

    for (int i = 0; i < n; i++) {
        cin >> x;
        check1 += do_hash(x, n);
    }

    for (int i = 0; i < n; i++) {
        cin >> x;
        check2 += do_hash(x, n);
    }

    if (!(check1 ^ check2)) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}