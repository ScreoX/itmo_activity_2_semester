#include <iostream>
#include "vector"
#include "Algorithms.h"
#include "Functions.h"

int main() {
    std::vector<int> s = {1,3,5};
    if (any_of(s.begin(), s.end(), anyOfDivisibleBy2<int>)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}
