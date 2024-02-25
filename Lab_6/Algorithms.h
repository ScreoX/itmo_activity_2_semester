#ifndef LAB_6_ALGORITHMS_H
#define LAB_6_ALGORITHMS_H

template<typename Iterator, typename obj>
bool any_of(const Iterator& begin, const Iterator& end, bool (&function)(obj));

template<typename Iterator, typename obj>
bool is_partitioned(const Iterator& begin, const Iterator& end, bool (&function)(obj));

template<typename Iterator, typename obj>
bool is_palindrome(const Iterator& begin, const Iterator& end, bool (&function)(obj));

#include "Algorithms.cpp"
#endif