#ifndef LAB_6_FUNCTIONS_H
#define LAB_6_FUNCTIONS_H

template<typename T>
bool anyOfDivisibleBy2 (T obj) {
    return obj % 2 == 0;
}

template<typename T>
bool isPartitioned (T obj, T elem) {
    return obj > elem;
}

template<typename T>
bool IsPalindrome (T obj1, T obj2) {
    return obj1 ^ obj2;
}

#endif
