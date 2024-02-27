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

template<typename iterator, typename obj1, typename obj2>
bool is_partitioned(const iterator& begin, const iterator& end, bool (&function)(obj1, obj2)) {
    for (iterator elem = begin; elem != end; elem++) {
        bool check[2] = {false, false};
        for (iterator i = begin; i != end; i++) {
            if (i != elem) {
                if (function(*i, *elem)) {
                    check[0] = true;
                } else {
                    check[1] = true;
                }
            }
        }
        if (check[0] && check[1]) {
            return true;
        }
    }
    return false;
}

template<typename iterator, typename obj1>
bool is_palindrome(const iterator& begin, const iterator& end, bool (&function)(obj1)) {
    for (iterator i = begin, j = end - 1; i != end, j != begin; i++, j--) {
        if (function(*i) ^ function(*j)) {
            return false;
        }
    }
    return true;
}
#endif