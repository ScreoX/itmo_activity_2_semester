#include "Colors.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef LRCUBE_SMALLCUBE_H
#define LRCUBE_SMALLCUBE_H

class Squares{
private:
    float X;
    float Y;
    float Z;
    float faceLeftBottom[3];
    float faceRightBottom[3];
    float faceLeftUp[3];
    float faceRightUp[3];
    float backLeftBottom[3];
    float backRightBottom[3];
    float backLeftUp[3];
    float backRightUp[3];

public:

    char sides_colors[6] = {0,1,2,3,4,5};
    //front left back right bottom up
    // orange blue red green white yellow
    void Draw(std::vector<Colors*> shaders, glm::mat4 MVP);
    void Init(float size);
    float GetX() const;
    float GetY() const;
    float GetZ() const;
    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);

    void turnleft(); // 0->1 1->2 2->3 3->0
    void turnright(); // 0->3 1->0 2->1 3->2
    void turnup(); // 0->5 5->2 2->4 4->0
    void turndown(); // 0->4 4->2 2->5 5->0
};

#endif
