#ifndef LAB4_OP_2SEM_PARALLELOGRAM_H
#define LAB4_OP_2SEM_PARALLELOGRAM_H
#include "Virtuals.h"


class Parallelogram : Figure {
private:

    CVector2D p1;
    CVector2D p2;
    CVector2D p3;
    CVector2D p4;

    double weight = 0;
    const char* name = "Parallelogram";

public:

    Parallelogram() ;

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