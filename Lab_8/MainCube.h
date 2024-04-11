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

struct Cords {
    GLfloat x;
    GLfloat y;
    GLfloat z;

    Cords(GLfloat first, GLfloat second, GLfloat third) : x(first), y(second), z(third) {}
};

class MainCube {
private:
    CordsSquares cords = {0,0,0};
    float size = 1.0f;
public:

    Squares squares[3][3][3];
    std::vector<std::pair<char,char>> stackSolve;
    std::vector<std::pair<char,char>> operations_show;
    std::vector<std::pair<char,char>> operations_back;


    // флаг трех типов
    // -1 - не считать в стек
    // 1 - считать в стек
    // 2 - записывать операции для сборки по алгоритму

    void turnVertical(int ver, int mode, int flag);
    void turnHorizontal(int hor, int mode, int flag);
    void turnAround(int side, int mode, int flag);

    void shuffle();
    void solve_with_stack();

    bool is_correct();

    void Draw(std::vector<Colors*> shaders, glm::mat4 MVP);
    void Init();

    void solve_with_algorithms();
    void show_operations_of_solving();
    void white_cross();
    void set_up_centers();
    static char find_center(int ver, int side);

    void go_back();
};

#endif
