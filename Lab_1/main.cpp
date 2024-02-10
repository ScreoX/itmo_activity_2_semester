#include <iostream>
#include "header.h"

void func1 () {
    std::cout << "\nTask 1:\n"
                 "Changes the larger of two variables by its remainder when divided by the second variable.\n";
    int x = 9, y = 5;
    std::cout << "Values: " << x << " " << y << '\n';

    max_div_min(x, y);
    std::cout << "Solution with links: \n" << x << " " << y << '\n';

    max_div_min(&x, &y);
    std::cout << "Solution with pointers: \n" << x << " " << y << '\n';

}

void func2 () {
    std::cout << "\nTask 2:\n"
                 "Rounds the number.\n";
    double x = 9.218;
    double y = 10.91;
    std::cout << "Values: " << x << " " << y << '\n';

    round_number(x);
    std::cout << "Solution with links: \n" << x << '\n';

    round_number(&y);
    std::cout << "Solution with pointers: \n" << y <<'\n';

}

void func3 () {
    std::cout << "\nTask 3:\n"
                 "Decreases the radius of a circle by a specified number.\n";
    circle obj;
    obj.r = 3;
    obj.x = 1;
    obj.y = 1;

    double x = 1;
    std::cout << "Values of circle: \n"
                 "x: " << obj.x << " y: " << obj.y << " radius: " << obj.r << "\n"
                                                                        "The radius should be reduced by " << x << '\n';

    reduce_radius_of_circle(obj, x);
    std::cout << "Solution with links: \n"
                 "New circle: \n"
                 "x: " << obj.x << " y: " << obj.y << " radius: " << obj.r << '\n';

    reduce_radius_of_circle(&obj, &x);
    std::cout << "Solution with pointers: \n"
                 "New circle: \n"
                 "x: " << obj.x << " y: " << obj.y << " radius: " << obj.r << '\n';

}

void func4 () {
    std::cout << "\nTask 4:\n"
                 "Transposes a 3x3 square matrix.\n";
    matrix m;
    m.a11 = 1;
    m.a12 = 2;
    m.a13 = 3;
    m.a21 = 4;
    m.a22 = 5;
    m.a23 = 6;
    m.a31 = 7;
    m.a32 = 8;
    m.a33 = 9;

    std::cout << "Matrix: \n" << m.a11 << " " << m.a12 << " " << m.a13 << '\n'
                                                                             << m.a21 << " " << m.a22 << " " << m.a23 << '\n'
                                                                             << m.a31 << " " << m.a32 << " " << m.a33 << '\n';


    transpose_matrix(m);
    std::cout << "Solution with links: \n"
          << m.a11 << " " << m.a12 << " " << m.a13 << '\n'
          << m.a21 << " " << m.a22 << " " << m.a23 << '\n'
          << m.a31 << " " << m.a32 << " " << m.a33 << '\n';

    transpose_matrix(&m);
    std::cout << "Solution with pointers: \n"
            << m.a11 << " " << m.a12 << " " << m.a13 << '\n'
            << m.a21 << " " << m.a22 << " " << m.a23 << '\n'
            << m.a31 << " " << m.a32 << " " << m.a33 << '\n';

}

int main() {

    func1();
    func2();
    func3();
    func4();

    return 0;
}
