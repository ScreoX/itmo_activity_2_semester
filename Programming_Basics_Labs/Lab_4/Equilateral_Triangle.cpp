#include "Equilateral_Triangle.h"
#include "iostream"
#include "cmath"

Equilateral_Triangle::Equilateral_Triangle() {
    this->Equilateral_Triangle::initFromDialog();
}

double Equilateral_Triangle::square() {

    double area = abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y)) / 2;

    return area;
}

double Equilateral_Triangle::perimeter() {

    double perimeter = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2))
            + sqrt(pow(p3.x - p2.x, 2) + pow(p3.y - p2.y, 2))
            + sqrt(pow(p3.x - p1.x, 2) + pow(p3.y - p1.y, 2));

    return perimeter;
}

double Equilateral_Triangle::mass() const {

    double figure_mass = weight;

    return figure_mass;
}

CVector2D Equilateral_Triangle::position() {

    CVector2D center;
    center.x = (p1.x + p2.x + p3.x) / 3;
    center.y = (p1.y + p2.y + p3.y) / 3;

    return center;
}

void Equilateral_Triangle::draw() {
    std::cout<<"Name of the Figure: " << classname() << '\n';
    std::cout<<"Position of center of the Figure: " << position() << '\n';
    std::cout<<"Weight of the Figure: " << weight << '\n';
    std::cout<<'\n';
}

void Equilateral_Triangle::initFromDialog() {

    std::cout << "Enter cords of the Equilateral_Triangle:\n"
                 "First cord:\n";
    std::cin>> p1;

    std::cout << "Second cord:\n";
    std::cin >> p2;

    std::cout << "Third cord:\n";
    std::cin >> p3;

    std::cout << "Weight:\n";
    std::cin >> weight;

}

const char* Equilateral_Triangle::classname() {

    const char* figure_name = name;

    return figure_name;
}

unsigned int Equilateral_Triangle::size() {

    unsigned int figure_size = sizeof(*this);

    return figure_size;
}

bool Equilateral_Triangle::operator==(const IPhysObject &obj) const {

    if (mass() == obj.mass()) {
        return true;
    }
    return false;
}

bool Equilateral_Triangle::operator>(const IPhysObject &obj) const {

    if (mass() > obj.mass()) {
        return true;
    }
    return false;
}

bool Equilateral_Triangle::operator<(const IPhysObject &obj) const {

    if (mass() < obj.mass()) {
        return true;
    }
    return false;
}
