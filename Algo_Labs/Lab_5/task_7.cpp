#include <iostream>
#include <vector>

using namespace std;

void quick_sort(vector<int>& mas, int left, int right) {
    int i = left;
    int j = right;
    int pivot = mas[(i + j) / 2 + 1];

    while (i <= j) {
        while (mas[i] < pivot)
            i++;
        while (mas[j] > pivot)
            j--;
        if (i <= j) {
            swap(mas[i], mas[j]);
            i++;
            j--;
        }
    }
    if (j > left)
        quick_sort(mas, left, j);
    if (i < right)
        quick_sort(mas, i, right);
}

int main() {

    int n;
    cin >> n;

    vector<int> degreesFirst(n, 0);

    int x, y;
    for (int i = 0; i < n - 1; i++) {
        cin >> x >> y;
        degreesFirst[x - 1]++;
        degreesFirst[y - 1]++;
    }

    quick_sort(degreesFirst, 0, n - 1);

    vector<int> degreesSecond(n, 0);

    for (int i = 0; i < n - 1; i++) {
        cin >> x >> y;
        degreesSecond[x - 1]++;
        degreesSecond[y - 1]++;
    }

    quick_sort(degreesSecond, 0, n - 1);

    for (int i = 0; i < n; i++) {
        if (degreesFirst[i] != degreesSecond[i]) {
            cout << "NO";
            return 0;
        }
    }

    cout << "YES";

    return 0;
}

