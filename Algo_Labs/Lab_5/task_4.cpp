#include "blazingio.hpp"
#include <vector>

using namespace std;

struct InfoStudentsInGroup {
    int points, isu_num;
};

int size_for_hash;

int doHash(int elem) {
    return ((elem * 37) % size_for_hash);
}

void deleteStudent(int isu_num, vector<InfoStudentsInGroup>& group) {
    for (InfoStudentsInGroup& i : group) {
        if (i.isu_num == isu_num) {
            i = {-123, -123};
            break;
        }
    }
}

void findStudentWithMaxPointsInGroup(vector<InfoStudentsInGroup>& group) {
    int maxPoints = -123;

    for (InfoStudentsInGroup& students : group) {
        maxPoints = max(students.points, maxPoints);
    }

    cout << maxPoints << '\n';
}

void findAveragePointsInGroup(vector<InfoStudentsInGroup>& group) {
    int pointsSum = 0;
    int countStudents = 0;

    for (InfoStudentsInGroup& students : group) {
        if (students.points != -123) {
            ++countStudents;
            pointsSum += students.points;
        }
    }

    cout << pointsSum / countStudents << '\n';
}

int main() {
    int m, q;
    cin >> m >> q;

    size_for_hash = m * 10;
    vector<vector<InfoStudentsInGroup>> tableOfGroups(size_for_hash);

    char command;
    int group, isu_num, points;

    for (int i = 0; i < q; i++) {
        cin >> command;
        if (command == '+') {
            cin >> group >> isu_num >> points;
            tableOfGroups[doHash(group)].emplace_back(points, isu_num);
        } else if (command == '-') {
            cin >> group >> isu_num;
            deleteStudent(isu_num, tableOfGroups[doHash(group)]);
        } else if (command == 'a') {
            cin >> group;
            findAveragePointsInGroup(tableOfGroups[doHash(group)]);
        } else if (command == 'm') {
            cin >> group;
            findStudentWithMaxPointsInGroup(tableOfGroups[doHash(group)]);
        }
    }

    return 0;
}
