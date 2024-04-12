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
    Cords cordsVisual = Cords(1, 1, 1);
    float size = 1.0f;
public:

    GLFWwindow* screen;
    std::vector<Colors*> colors;
    int init();
    void load();
    void save();
    void drawCube(Cords cords);
    static void changePositions(MainCube &mainScreen);

    Squares squares[3][3][3];
    std::vector<std::pair<char,char>> stackSolve;
    std::vector<std::pair<char,char>> operations_show;
    std::vector<std::pair<char,char>> operations_back;

    bool check_white_cross[4] = {false, false, false, false};
    bool check_white_corners[4] = {false, false, false, false}; // 0 - зеленый красный, 1 - зеленый оранжевый, 2 - синий красный, 3 - синий оранжевый

    // флаг трех типов
    // -1 - не считать в стек
    // 1 - считать в стек
    // 2 - записывать операции для сборки по алгоритму

    void turnVertical(int ver, int mode, int flag);
    void turnHorizontal(int hor, int mode, int flag);
    void turnAround(int side, int mode, int flag);

    void pifpaf_red_yellow_green();
    void pifpaf_red_white_green();
    void pifpaf_red_yellow_blue();
    void pifpaf_red_white_blue();
    void pifpaf_orange_yellow_green();
    void pifpaf_orange_white_green();
    void pifpaf_orange_yellow_blue();
    void pifpaf_orange_white_blue();


    void shuffle();
    void solve_with_stack();

    void Draw(std::vector<Colors*> shaders, glm::mat4 MVP);
    void Init();

    void solve_with_algorithms();

    void white_cross();
    void set_up_centers();
    void check_centers(int round);
    static char find_center(int ver, int side);
    bool checkWhiteCross();
    void complete_colors();

    void white_corners();
    bool check_corners();
    void put_white_corners();
};

#endif
