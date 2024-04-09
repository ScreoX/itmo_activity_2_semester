#include "MainCube.h"
#include "windows.h"

void MainCube::shuffle() {
    int countOperations = 5;
    FILE* save = fopen("../OutputAndInput/input.txt", "w");
    char way, id, orientation;
    for (int i = 0; i < countOperations; i++) {
        way = rand()%3;
        id = rand()%3;
        if (way == 0) {
            orientation = rand() % 2 + 2;
            turnHorizontal(id, orientation);
            if (orientation == left) stackSolve.emplace_back(id, right);
            if (orientation == right) stackSolve.emplace_back(id, left);
        }
        else if (way == 1){
            orientation = rand() % 2;
            turnVertical(id, orientation);
            if (orientation == down) stackSolve.emplace_back(id, up);
            if (orientation == up) stackSolve.emplace_back(id, down);
        }
        else {
            orientation = rand() % 2 + 4;
            turnAround(id, orientation);
            if (orientation == round_left) stackSolve.emplace_back(id, round_right);
            if (orientation == round_right) stackSolve.emplace_back(id, round_left);
        }
        glLoadIdentity();
        glFinish();
        std::putc(way+97,save);
        std::putc(id+97,save);
        std::putc(orientation+98,save);
    }

    std::fclose(save);
}

void MainCube::Draw(std::vector<Colors*> colors, glm::mat4 MVP) {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                squares[x][y][z].Draw(colors, MVP);
            }
        }
    }
}

void MainCube::Init() {
    X = Y = Z = 0;
    size = 1.0f;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                squares[x][y][z].SetX(float(x - 1)*(size/3));
                squares[x][y][z].SetY(float(y - 1)*(size/3));
                squares[x][y][z].SetZ(float(z - 1)*(size/3));
                squares[x][y][z].Init(size);
            }
        }
    }
}

void MainCube::turnVertical(int ver, int orientation) {

    if (orientation == down) {
        stackSolve.emplace_back(ver, up);
    } else {
        stackSolve.emplace_back(ver, down);
    }

    for (int y = 0; y < 3; y++) {
        for (int z = 0; z < 3; z++) {
            if (orientation == down) {
                squares[ver][y][z].turndown();
            }
            else {
                squares[ver][y][z].turnup();
            }
        }
    }

    Squares move_1 = squares[ver][0][0], move_2 = squares[ver][0][2], move_3 = squares[ver][2][2], move_4 = squares[ver][2][0];

    if (orientation == down) {
        for (int i = 0; i < 6; i++) {
            squares[ver][2][0].FindSide(i, move_1.Side(i));
            squares[ver][2][2].FindSide(i, move_4.Side(i));
            squares[ver][0][0].FindSide(i, move_2.Side(i));
            squares[ver][0][2].FindSide(i, move_3.Side(i));
        }
        move_1 = squares[ver][1][0], move_2 = squares[ver][0][1], move_3 = squares[ver][1][2], move_4 = squares[ver][2][1];

        for (int i = 0; i < 6; i++) {
            squares[ver][1][0].FindSide(i, move_2.Side(i));
            squares[ver][0][1].FindSide(i, move_3.Side(i));
            squares[ver][1][2].FindSide(i, move_4.Side(i));
            squares[ver][2][1].FindSide(i, move_1.Side(i));
        }
    }
    else if (orientation == up) {
        for (int i = 0; i < 6; i++) {
            squares[ver][2][0].FindSide(i, move_3.Side(i));
            squares[ver][0][2].FindSide(i, move_1.Side(i));
            squares[ver][2][2].FindSide(i, move_2.Side(i));
            squares[ver][0][0].FindSide(i, move_4.Side(i));
        }
        move_1 = squares[ver][1][0], move_2 = squares[ver][0][1], move_3 = squares[ver][1][2], move_4 = squares[ver][2][1];
        for (int i = 0; i < 6; i++) {
            squares[ver][1][0].FindSide(i, move_4.Side(i));
            squares[ver][0][1].FindSide(i, move_1.Side(i));
            squares[ver][1][2].FindSide(i, move_2.Side(i));
            squares[ver][2][1].FindSide(i, move_3.Side(i));
        }
    }
}

void MainCube::turnHorizontal(int indHor, int orientation) {

    if (orientation == left) {
        stackSolve.emplace_back(indHor, right);
    } else {
        stackSolve.emplace_back(indHor, left);
    }

    for (int vert = 0; vert < 3; vert++) {
        for (int round = 0; round < 3; round++) {
            if (orientation == left) {
                squares[vert][indHor][round].turnleft();
            }
            else if (orientation == right) {
                squares[vert][indHor][round].turnright();
            }
        }
    }
    Squares move_1 = squares[0][indHor][0], move_2 = squares[0][indHor][2], move_3 = squares[2][indHor][2], move_4 = squares[2][indHor][0];
    if (orientation == right) {
        for (int i = 0; i < 6; i++) {
            squares[0][indHor][2].FindSide(i, move_1.Side(i));
            squares[2][indHor][2].FindSide(i, move_2.Side(i));
            squares[2][indHor][0].FindSide(i, move_3.Side(i));
            squares[0][indHor][0].FindSide(i, move_4.Side(i));
        }
        move_1 = squares[1][indHor][0], move_2 = squares[0][indHor][1], move_3 = squares[1][indHor][2], move_4 = squares[2][indHor][1];
        for (int i = 0; i < 6; i++) {
            squares[0][indHor][1].FindSide(i,move_1.Side(i));
            squares[1][indHor][2].FindSide(i,move_2.Side(i));
            squares[2][indHor][1].FindSide(i,move_3.Side(i));
            squares[1][indHor][0].FindSide(i,move_4.Side(i));
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            squares[2][indHor][0].FindSide(i,move_1.Side(i));
            squares[2][indHor][2].FindSide(i,move_4.Side(i));
            squares[0][indHor][0].FindSide(i,move_2.Side(i));
            squares[0][indHor][2].FindSide(i,move_3.Side(i));
        }
        move_1 = squares[1][indHor][0], move_2 = squares[0][indHor][1], move_3 = squares[1][indHor][2], move_4 = squares[2][indHor][1];
        for (int i = 0; i < 6; i++) {
            squares[2][indHor][1].FindSide(i,move_1.Side(i));
            squares[1][indHor][0].FindSide(i,move_2.Side(i));
            squares[0][indHor][1].FindSide(i,move_3.Side(i));
            squares[1][indHor][2].FindSide(i,move_4.Side(i));
        }
    }
}

void MainCube::turnAround(int edge, int orientation) {

    if (orientation == round_right) {
        stackSolve.emplace_back(edge, round_left);
    } else {
        stackSolve.emplace_back(edge, round_right);
    }

    for (int vert = 0; vert < 3; vert++) {
        for (int y = 0; y < 3; y++) {
            squares[vert][y][edge].turndown();
            if (orientation == round_right) {
                squares[vert][y][edge].turnright();
            }
            else if (orientation == round_left){
                squares[vert][y][edge].turnleft();
            }
            squares[vert][y][edge].turnup();
        }
    }
    Squares move_1 = squares[0][0][edge], move_2 = squares[2][0][edge], move_3 = squares[2][2][edge], move_4 = squares[0][2][edge];
    if (orientation == round_left) {
        for (int i = 0; i < 6; i++) {
            squares[2][0][edge].FindSide(i,move_1.Side(i));
            squares[2][2][edge].FindSide(i,move_2.Side(i));
            squares[0][2][edge].FindSide(i,move_3.Side(i));
            squares[0][0][edge].FindSide(i,move_4.Side(i));
        }
        move_1 = squares[0][1][edge], move_2 = squares[1][2][edge], move_3 = squares[2][1][edge], move_4 = squares[1][0][edge];
        for (int i = 0; i < 6; i++) {
            squares[2][1][edge].FindSide(i,move_4.Side(i));
            squares[1][2][edge].FindSide(i,move_3.Side(i));
            squares[0][1][edge].FindSide(i,move_2.Side(i));
            squares[1][0][edge].FindSide(i,move_1.Side(i));
        }
    }
    else if (orientation == round_right) {
        for (int i = 0; i < 6; i++) {
            squares[0][2][edge].FindSide(i,move_1.Side(i));
            squares[2][2][edge].FindSide(i,move_4.Side(i));
            squares[2][0][edge].FindSide(i,move_3.Side(i));
            squares[0][0][edge].FindSide(i,move_2.Side(i));
        }
        move_1 = squares[0][1][edge], move_2 = squares[1][2][edge], move_3 = squares[2][1][edge], move_4 = squares[1][0][edge];
        for (int i = 0; i < 6; i++) {
            squares[1][2][edge].FindSide(i,move_1.Side(i));
            squares[2][1][edge].FindSide(i,move_2.Side(i));
            squares[1][0][edge].FindSide(i,move_3.Side(i));
            squares[0][1][edge].FindSide(i,move_4.Side(i));
        }
    }
}

void MainCube::solve() { // не работает время

    for (int i = stackSolve.size() - 1; i >= 0; i--) {
        auto [index, operation] = stackSolve[i];

//        double startTime = glfwGetTime();

        if (operation == up || operation == down) {
            turnVertical(index, operation);
//            while (glfwGetTime() - startTime < 0.5) {}
        }
        else if (operation == left || operation == right) {
            turnHorizontal(index, operation);
//            while (glfwGetTime() - startTime < 0.5) {}
        }
        else if (operation == round_left || operation == round_right) {
            turnAround(index, operation);
//            while (glfwGetTime() - startTime < 0.5) {}
        }
    }
    std::vector<std::pair<char, char>> new_stack;
    stackSolve = new_stack;
}