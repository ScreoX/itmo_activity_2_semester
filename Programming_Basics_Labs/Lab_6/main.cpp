#include <iostream>
#include "vector"
#include "Algorithms.h"
#include "Complex.h"

template<typename T>
bool anyOfLessThanZero (T obj) {
    return obj < 0;
}

template<typename T>
bool isPartitioned (T obj, T elem) {
    return obj == elem;
}

template<typename T>
bool isPalindrome (T obj1) {
    return obj1 > 0;
}

int main() {

    std::cout << "Int Vector:\n";
    std::vector<int> v_nums = {2,2,5};
    std::vector<int>::iterator itr_for_int;
    for (itr_for_int = v_nums.begin(); itr_for_int != v_nums.end(); itr_for_int++) {
        std::cout << *itr_for_int << " ";
    }

    std::cout << "\nAny of numbers less than zero:\n";
    if (any_of(v_nums.begin(), v_nums.end(), anyOfLessThanZero<int>)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    std::cout << "Numbers can be partitioned by predicate (equal):\n";
    if (is_partitioned(v_nums.begin(), v_nums.end(), isPartitioned<int>)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    std::cout << "Numbers of vector represent palindrome by predicate(Int num larger than zero):\n";
    if (is_palindrome(v_nums.begin(), v_nums.end(), isPalindrome<int>)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }


    std::cout << "\nComplex Vector\n";

    Complex x(1,4);
    Complex y(1,4);
    Complex z(-2, -10);
    std::vector<Complex> v_complex_nums = {x, y, z};

    std::vector<Complex>::iterator itr_for_complex;
    for (itr_for_complex = v_complex_nums.begin(); itr_for_complex != v_complex_nums.end(); itr_for_complex++) {
        if (itr_for_complex->im >= 0) {
            std::cout << itr_for_complex->re << " + " << itr_for_complex->im << "i\n";
        } else {
            std::cout << itr_for_complex->re << " - " << itr_for_complex->im * -1 << "i\n";
        }
    }

    std::cout << "Any of numbers have less than zero:\n";
    if (any_of(v_complex_nums.begin(), v_complex_nums.end(), anyOfLessThanZero<Complex>)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    std::cout << "Numbers can be partitioned by predicate (equal):\n";
    if (is_partitioned(v_complex_nums.begin(), v_complex_nums.end(), isPartitioned<Complex>)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    std::cout << "Numbers of vector represent palindrome by predicate(Complex num larger than zero):\n";
    if (is_palindrome(v_complex_nums.begin(), v_complex_nums.end(), isPalindrome<Complex>)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}
