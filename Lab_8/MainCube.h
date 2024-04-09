#include "Squares.h"
#include "vector"
#ifndef RUBIK_CUBE_CUBE_H
#define RUBIK_CUBE_CUBE_H

enum Combinations {
    up = 0,
    down,
    left,
    right,
    round_left,
    round_right,
};

enum LevelsHorizontal {
    lowHor = 0,
    middleHor,
    upHor,
};

enum LevelsVertical {
    leftVert = 0,
    centralVert,
    rightVert,
};

enum LevelsAround {
    farAround = 0,
    centerAround,
    nearAround,
};

class MainCube {
private:
    float X = 0;
    float Z = 0;
    float Y = 0;
    float size = 1.0f;
public:
    Squares squares[3][3][3];
    std::vector<std::pair<char,char>> stackSolve;

    void turnHorizontal(int hor, int mode);
    void turnVertical(int ver, int mode);
    void turnAround(int side, int mode);
    void shuffle();
    bool is_correct();
    void solve();

    void Draw(std::vector<Colors*> shaders, glm::mat4 MVP);
    void Init();

    void al1(); // нижний крест
    void al2(); // нижний полный часть среднего
    void al3(); // два нижних слоя
    void al4(); // верхний крест
    void al5(); // угловые верх на свои места
    void al6(); // ориентация верхних угловых кубиков
};

#endif
