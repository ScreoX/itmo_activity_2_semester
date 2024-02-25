#ifndef LAB_6_ALGORITHMS_H
#define LAB_6_ALGORITHMS_H

template<typename iterator, typename obj>
bool any_of(const iterator& begin, const iterator& end, bool (&function)(obj)) {
    for (iterator i = begin; i != end; i++) {
        if (function(*i)) {
            return true;
        }
    }
    return false;
}

template<typename Iterator, typename obj>
bool is_partitioned(const Iterator& begin, const Iterator& end, bool (&function)(obj)) {
    for (Iterator elem = begin; elem != end; elem++) {
        bool check = false;
        for (Iterator i = begin; i != end && i != elem; i++) {
            if (function(*i, *elem)) {
                if (check) {
                    return true;
                }
                check = true;
            }
        }
    }
    return false;
}

template<typename Iterator, typename obj>
bool is_palindrome(const Iterator& begin, const Iterator& end, bool (&function)(obj)) {
    for (Iterator i = begin, j = end - 1; i != end, j != begin; i++, j--) {
        if (function(*i, *j)) {
            return false;
        }
    }
    return true;
}
#endif