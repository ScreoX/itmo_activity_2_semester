#ifndef LAB4_OP_2SEM_EQUILATERAL_TRIANGLE_H
#define LAB4_OP_2SEM_EQUILATERAL_TRIANGLE_H
#include "Virtuals.h"


class Equilateral_Triangle : Figure {
private:

    CVector2D p1;
    CVector2D p2;
    CVector2D p3;

    double weight = 0;
    const char* name = "Parallelogram";

public:

    Equilateral_Triangle() ;

    double square() override;
    double perimeter() override;
    double mass() const override;
    CVector2D position() override;
    void draw() override;
    void initFromDialog() override;
    const char* classname() override;
    unsigned int size() override;

    bool operator==(const IPhysObject& obj) const override;
    bool operator>(const IPhysObject& obj) const override;
    bool operator<(const IPhysObject& obj) const override;
};


#endif
