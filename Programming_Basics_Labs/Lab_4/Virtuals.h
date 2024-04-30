#ifndef LAB4_OP_2SEM_VIRTUALS_H
#define LAB4_OP_2SEM_VIRTUALS_H
#include "iostream"


class IGeoFig {
public:
    virtual double square() = 0;
    virtual double perimeter() = 0;
};

class CVector2D {
public:
    double x,y;
    CVector2D();

    friend std::istream& operator>>(std::istream&, CVector2D&);
    friend std::ostream& operator<<(std::ostream&, const CVector2D&);
};

class IPhysObject {
public:
    virtual double mass() const = 0;
    virtual CVector2D position() = 0;
    virtual bool operator==(const IPhysObject& obj) const = 0;
    virtual bool operator>(const IPhysObject& obj) const = 0;
    virtual bool operator<(const IPhysObject& obj) const = 0;
};

class IPrintable {
public:
    virtual void draw() = 0;
};

class IDialogInitiable {
public:
    virtual void initFromDialog() = 0;
};

class BaseCObject {
public:
    virtual const char* classname() = 0;
    virtual unsigned int size() = 0;
};

class IFigure: public IGeoFig, public IPhysObject, public IPrintable, public IDialogInitiable, public BaseCObject {};

#endif
