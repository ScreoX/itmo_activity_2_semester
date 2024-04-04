#ifndef CUBE_RUBE_CUBE_H
#define CUBE_RUBE_CUBE_H
#include <iostream>
/*

Blue
0 1 2
3 4 5
6 7 8

Red
9 10 11
12 13 14
15 16 17

Yellow
18 19 20
21 22 23
24 25 26

Green
27 28 29
30 31 32
33 34 35

Orange
36 37 38
39 40 41
42 43 44

White
45 46 47
48 49 50
51 52 53

Cube


        18 19 20
        21 22 23
        24 25 26

0 1 2   9 10 11     27 28 29    36 37 38
3 4 5   12 13 14    30 31 32    39 40 41
6 7 8   15 16 17    33 34 35    42 43 44

        45 46 47
        48 49 50
        51 52 53


 */

struct Side {

    enum sides
    {
        top,
        bottom,
        front,
        back,
        left,
        right,
    };

    int cube[9];

};

struct Block
{
    int top, bottom, front, back, left, right;
};

struct InfoCorners {
    std::pair<int, int> pos{}; //side, first, second
    std::tuple<int,int,int> color{};
};

struct InfoSquares {
    std::tuple<int, int, int> pos{}; //side, first, second
    std::pair<int,int> color{};
};

/*
 * -------------------
 * |(0,0) (0,1) (0,2)|
 * |(1,0) (1,1) (1,2)|
 * |(2,0) (2,1) (2,2)|
 * -------------------
 *
 * top level = 0
 * middle level = 1
 * bottom level = 2
 *
 *
0 - White
1 - Yellow
2 - Red
3 - Blue
4 - Orange
5 - Green
 */

class Cube {
private:

    InfoCorners corners[8];
    InfoSquares squares[12];

public:

    void GenerateCube();
    void SolvedCube();

};


#endif
