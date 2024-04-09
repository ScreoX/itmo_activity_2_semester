#include "MainCube.h"

#ifndef LRCUBE_CUBEDLG_H
#define LRCUBE_CUBEDLG_H

struct Cords {
    GLfloat x;
    GLfloat y;
    GLfloat z;

    Cords(GLfloat first, GLfloat second, GLfloat third) : x(first), y(second), z(third) {}
};

class CubeDlg {
private:
    Cords cords = Cords(1, 1, 1);
public:
    GLFWwindow* screen;
    std::vector<Colors*> colors;
    int init();
    void load();
    void save();
    void drawCube(Cords cords);
    static void changePositions(CubeDlg &mainScreen);
    MainCube MyCube;
};

#endif