#include "header.h"

void max_div_min(int& x, int& y) {
    if (x > y) {
        x = x % y;
    } else {
        y = y % x;
    }
}

void max_div_min(int* x, int* y) {
    if (*x > *y) {
        *x = *x % *y;
    } else {
        *y = *y % *x;
    }
}

void round_number(double& num) {
    num = (int)num;
}

void round_number(double* num) {
    *num = (int)(*num);
}

void reduce_radius_of_circle(circle& obj, double& x) {
    obj.r -= x;
}

void reduce_radius_of_circle(circle* obj, double* x) {
    obj->r -= *x;
}

void transpose_matrix(matrix& obj) {

    int temp = obj.a12;
    obj.a12 = obj.a21;
    obj.a21 = temp;

    temp = obj.a13;
    obj.a13 = obj.a31;
    obj.a31 = temp;

    temp = obj.a23;
    obj.a23 = obj.a32;
    obj.a32 = temp;

}

void transpose_matrix(matrix* obj) {

    int temp = obj->a12;
    obj->a12 = obj->a21;
    obj->a21 = temp;

    temp = obj->a13;
    obj->a13 = obj->a31;
    obj->a31 = temp;

    temp = obj->a23;
    obj->a23 = obj->a32;
    obj->a32 = temp;
}
