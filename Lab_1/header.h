#ifndef LAB_1_HEADER_H
#define LAB_1_HEADER_H

void max_div_min(int&, int&);
void max_div_min(int*, int*);

void round_number(double&);
void round_number(double*);

struct circle {
    double x;
    double y;
    double r;
};

void reduce_radius_of_circle(circle&, double& x);
void reduce_radius_of_circle(circle*, double* x);

struct matrix {
    int a11, a12, a13, a21, a22, a23, a31, a32, a33;
};

/*
 matrix:
 a11 a12 a13
 a21 a22 a23
 a31 a32 a33
 */
void transpose_matrix(matrix&);
void transpose_matrix(matrix*);

#endif //LAB_1_HEADER_H
