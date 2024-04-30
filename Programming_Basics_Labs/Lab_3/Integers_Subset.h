#ifndef LAB_3_INTEGERS_SUBSET_H
#define LAB_3_INTEGERS_SUBSET_H


class Integers_Subset {

public:

    int subset[10];

    Integers_Subset();
    Integers_Subset(int mas[10]);

    Integers_Subset operator+(Integers_Subset& another);
    bool operator!=(Integers_Subset& another);
    bool operator==(Integers_Subset& another);
    Integers_Subset operator+=(int num);
    Integers_Subset operator-=(int num);

};


#endif
