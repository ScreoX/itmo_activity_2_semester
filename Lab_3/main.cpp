#include <iostream>
#include "Complex.h"
#include "Integers_Subset.h"



int main() {
    Complex a(1, 2);
    Complex b(3, 6);

    Complex c = a * b;
    double l = c|=c;

    std::cout << "Complex number c: " << c.re << " + " << c.im << "i\n"
                                                                "Lenght: " << l << '\n';

    int num = 2;
    a *= num;
    std::cout << "Complex number a: " << a.re << " + " << a.im << "i\n"
                                                                  "Complex number after multiply by " << num << ": " << a.re << " + " << a.im << "i\n";



    int mas1[10] = {0, 1, 2, 3, 4, -1, -1,-1,-1, 9};
    int mas2[10] = {0, 1, -1,-1,-1,-1, 6, 7 ,8 ,9};

    Integers_Subset sub1(mas1);
    Integers_Subset sub2(mas2);
    Integers_Subset sub3 = sub1 + sub2;

    std::cout << "\nFirst Subset: \n";
    for (int i : sub1.subset) {
        if (i != -1) {
            std::cout << i << " ";
        }
    }
    std::cout << "\nSecond Subset: \n";
    for (int i : sub2.subset) {
        if (i != -1) {
            std::cout << i << " ";
        }
    }
    std::cout << "\nUnion First and Second Subsets:\n";
    for (int i : sub3.subset) {
        if (i != -1) {
            std::cout << i << " ";
        }
    }
    std::cout << '\n';

    std::cout << "\nCheck: Sub1 != Sub2? ";
    bool check_1 = sub1 != sub2;
    if (check_1) {
        std::cout << "True\n";
    } else {
        std::cout << "False\n";
    }

    std::cout << "Check: Sub1 == Sub2? ";
    bool check_2 = sub1 == sub2;
    if (check_2) {
        std::cout << "True\n";
    } else {
        std::cout << "False\n";
    }


    std::cout << "\nFirst Subset: ";
    for (int i : sub1.subset) {
        if (i != -1) {
            std::cout << i << ' ';
        }
    }
    int num_1 = 7;
    std::cout << "\nAdd to First Subset " << num_1 << "\n"
                                                   "Updated First Subset: ";
    sub1 += num_1;

    for (int i : sub1.subset) {
        if (i != -1) {
            std::cout << i << ' ';
        }
    }
    std::cout << '\n';

    std::cout << "\nSecond Subset: ";
    for (int i : sub2.subset) {
        if (i != -1) {
            std::cout << i << ' ';
        }
    }
    int num_2 = 0;
    std::cout << "\nDelete from Second Subset " << num_2 << "\n"
                                                    "Updated Second Subset: ";
    sub2 -= num_2;

    for (int i : sub2.subset) {
        if (i != -1) {
            std::cout << i << ' ';
        }
    }



    return 0;
}
