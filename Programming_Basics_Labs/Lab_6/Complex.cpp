#include "Complex.h"
#include "cmath"

Complex::Complex() {
    re = 0, im = 0;
}

Complex::Complex(double x) {
    re = x;
}

Complex::Complex(double x, double y) {
    re = x;
    im = y;
}

Complex Complex::operator*(Complex &another) const {

    Complex NewComplex;
    if (another.im != 0) {
        NewComplex.re = (re * another.re) - (im * another.im);
        NewComplex.im = (re * another.im) + (im * another.re);
    } else {
        NewComplex.re = re * another.re;
        NewComplex.im = im * another.im;
    }

    return NewComplex;
}

Complex Complex::operator+(Complex &another) const {

    Complex NewComplex;
    NewComplex.re = re + another.re;
    NewComplex.im = im + another.im;

    return NewComplex;
}

double Complex::operator|=(Complex &same) const {

    double lenght = sqrt(re*re + im*im);

    return lenght;
}

Complex Complex::operator*=(double num) {
    re *= num;
    im*=num;
    return {};
}

Complex::operator double() const {
    double lenght = sqrt(re*re + im*im);

    return lenght;
}

bool Complex::operator<(int num) const {
    if (re < 0 && im < 0) {
        return true;
    }
    return false;
}

bool Complex::operator>(int num) const {
    if (re > 0 && im > 0) {
        return true;
    }
    return false;
}

bool Complex::operator==(Complex &obj) const {
    if (re == obj.re && im == obj.im) {
        return true;
    }
    return false;
}


