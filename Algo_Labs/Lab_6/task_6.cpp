#include <iostream>
#include <regex>

using namespace std;

int main() {

    regex regexString(R"([A-Z][a-z]+\s[A-Z][a-z]+\s[A-Z][a-z]+\s(\d{2})+\s(((\+7)|8|7)((\d{10})|(\(\d{3}\)((\d{3}-\d{4})|(-\d{3}(-\d{2}){2})))))+\s(g\.[A-Z]{3}\,+\sul\.[A-Z][a-z]+\,+\sd\.\d{2,}))");

    int m;
    cin >> m;
    cin.ignore();

    string input;

    for (int i = 0; i < m; i++) {

        getline(cin, input);

        if (regex_match(input, regexString)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}