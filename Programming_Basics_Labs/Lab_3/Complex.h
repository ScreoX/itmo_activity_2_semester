#ifndef LAB_3_COMPLEX_H
#define LAB_3_COMPLEX_H


class Complex {

public:

    double re;
    double im;

public:

    Complex();
    explicit Complex(double re);
    Complex(double re, double im);

    Complex operator*(Complex& another) const;
    Complex operator*=(double num);
    Complex operator+(Complex& another) const;
    double operator|=(Complex& same) const;
    operator double() const;

};


#endif
