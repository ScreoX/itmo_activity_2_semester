#include "Colors.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef LRCUBE_SMALLCUBE_H
#define LRCUBE_SMALLCUBE_H

struct CordsSquares {
    float x,y,z;
};

struct Sides {
    float frontLeftBottom[3];
    float frontRightBottom[3];
    float frontLeftUp[3];
    float frontRightUp[3];
    float backLeftBottom[3];
    float backRightBottom[3];
    float backLeftUp[3];
    float backRightUp[3];
};

enum ColorsCubes {
    orange = 0,
    blue,
    red,
    green,
    white,
    yellow,
};

class Squares {
private:
    
    CordsSquares cords{};
    Sides all_sides{};

public:

    char sides_colors[6] = {0,1,2,3,4,5};

    //front left back right bottom up
    // orange blue red green white yellow

    void Draw(std::vector<Colors*> shaders, glm::mat4 MVP);
    void Init(float size);

    [[nodiscard]] CordsSquares GetCords() const;
    void ChangeCords(float x, float y, float z);

    void FindSide(int index, char color);

    void turnleft();
    void turnright();
    void turnup();
    void turndown();
};

#endif
