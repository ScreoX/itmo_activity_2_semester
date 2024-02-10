#include "Integers_Subset.h"


Integers_Subset::Integers_Subset() {
    for (int i = 0; i < 10; i++) {
        subset[i] = -1;
    }
}

Integers_Subset Integers_Subset::operator+(Integers_Subset &another) {

    Integers_Subset NewSubset;
    int counting_mas[10] = {0};

    for (int i = 0; i < 10; i++) {
        if (subset[i] != -1) {
            ++counting_mas[i];
        }
    }

    for (int i = 0; i < 10; i++) {
        if (another.subset[i] != -1) {
            ++counting_mas[i];
        }
    }

    for (int i = 0; i < 10; i++) {
        if (counting_mas[i] > 0) {
            NewSubset.subset[i] = i;
        }
    }

    return NewSubset;
}

Integers_Subset::Integers_Subset(int *mas) {
    for (int i = 0; i < 10; i++) {
        subset[i] = mas[i];
    }
}

bool Integers_Subset::operator!=(Integers_Subset &another) {
    int count = 0;

    for (int i = 0; i < 10; i++) {
        if (subset[i] == another.subset[i]) {
            ++count;
        }
    }
    if (count == 10) {
        return false;
    }
    return true;
}

bool Integers_Subset::operator==(Integers_Subset &another) {
    for (int i = 0; i < 10; i++) {
        if (subset[i] != another.subset[i]) {
            return false;
        }
    }
    return true;
}

Integers_Subset Integers_Subset::operator+=(int num) {
    subset[num] = num;
    return subset;
}

Integers_Subset Integers_Subset::operator-=(int num) {
    subset[num] = -1;
    return subset;
}
