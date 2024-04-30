#include <iostream>
#include <vector>
#include <queue>
#include "algorithm"


using namespace std;

bool find_person_for_cat(vector<vector<int>>& PeoplePrefer, int ind, int first, int second) {
    for (int i : PeoplePrefer[ind]) {
        if (i == first) {
            return true;
        }
        if (i == second) {
            return false;
        }
    }

    return false;
}

int main() {

    int n;
    cin >> n;

    queue<int> freeMen;

    int person;
    vector<vector<int>> CatsPrefer(2 * n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> person;
            CatsPrefer[i][j] = person + n;
        }
        freeMen.push(i);
    }

    int cat;
    vector<vector<int>> PeoplePrefer(2 * n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> cat;
            PeoplePrefer[i + n][j] = cat;
        }
    }

    vector<int> cat_of_every_person(2 * n, -1);
    vector<bool> free_cats(n, true);

    while (!freeMen.empty()) {
        int free_person = freeMen.front();
        freeMen.pop();
        for (int i = 0; i < n; ++i) {
            if (free_cats[free_person]) {
                person = CatsPrefer[free_person][i];
                if (cat_of_every_person[person] == -1) {
                    cat_of_every_person[person] = free_person;
                    free_cats[free_person] = false;
                } else {
                    cat = cat_of_every_person[person];
                    if (find_person_for_cat(PeoplePrefer, person, free_person, cat)) {
                        cat_of_every_person[person] = free_person;
                        free_cats[free_person] = false;
                        free_cats[cat] = true;
                        freeMen.push(cat);
                    }
                }
            }
        }
    }

    vector<pair<int,int>> answer(n);

    for (int i = 0; i < n; i++) {
        answer[i] = {cat_of_every_person[i + n], i};
    }

    sort(answer.begin(), answer.end());

    for (int i = 0; i < n; i++) {
        cout << answer[i].first << " " << answer[i].second << '\n';
    }

    return 0;
}

