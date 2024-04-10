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
    CordsSquares cords = {0,0,0};
    float size = 1.0f;
public:
    Squares squares[3][3][3];
    std::vector<std::pair<char,char>> stackSolve;

    void turnHorizontal(int hor, int mode, bool flag);
    void turnVertical(int ver, int mode, bool flag);
    void turnAround(int side, int mode, bool flag);
    void shuffle();
    bool is_correct();
    void solve();

    void Draw(std::vector<Colors*> shaders, glm::mat4 MVP);
    void Init();
};

#endif
