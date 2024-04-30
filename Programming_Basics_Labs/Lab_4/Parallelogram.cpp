#include "Parallelogram.h"
#include "iostream"
#include "cmath"

Parallelogram::Parallelogram() {
    Parallelogram::initFromDialog();
}

double Parallelogram::square() {

    double area = abs((p2.x - p1.x) * (p3.y - p2.y) - (p3.x - p2.x) * (p2.y - p1.y));

    return area;
}
double FindDistanceBetweenPoints (CVector2D first, CVector2D second) {

    double distance = sqrt(pow(second.x - first.x, 2) + pow(second.y - first.y, 2));

    return distance;
}
double Parallelogram::perimeter() {

    double perimeter = FindDistanceBetweenPoints(p1, p2) +
            FindDistanceBetweenPoints(p2, p3) +
            FindDistanceBetweenPoints(p3, p4) +
            FindDistanceBetweenPoints(p4, p1);

    return perimeter;
}

double Parallelogram::mass() const {

    double figure_mass = weight;

    return figure_mass;
}

CVector2D Parallelogram::position() {

    CVector2D center;
    center.x = (p1.x + p2.x + p3.x + p4.x) / 4;
    center.y = (p1.y + p2.y + p3.y + p4.y) / 4;

    return center;
}

void Parallelogram::draw() {
    std::cout<<"Name of the Figure: " << classname() << '\n';
    std::cout<<"Position of center of the Figure: " << position() << '\n';
    std::cout<<"Weight of the Figure: " << weight << '\n';
    std::cout<<'\n';
}

void Parallelogram::initFromDialog() {

    std::cout << "Enter cords of the Parallelogram:\n"
                 "First cord:\n";
    std::cin>> p1;

    std::cout << "Second cord:\n";
    std::cin >> p2;

    std::cout << "Third cord:\n";
    std::cin >> p3;

    std::cout << "Fourth cord:\n";
    std::cin >> p4;

    std::cout << "Weight:\n";
    std::cin >> weight;

}

const char* Parallelogram::classname() {

    const char* figure_name = name;

    return figure_name;
}

unsigned int Parallelogram::size() {

    unsigned int figure_size = sizeof(*this);

    return figure_size;
}

bool Parallelogram::operator==(const IPhysObject &obj) const {

    if (mass() == obj.mass()) {
        return true;
    }
    return false;
}

bool Parallelogram::operator>(const IPhysObject &obj) const {

    if (mass() > obj.mass()) {
        return true;
    }
    return false;
}

bool Parallelogram::operator<(const IPhysObject &obj) const {

    if (mass() < obj.mass()) {
        return true;
    }
    return false;
}



