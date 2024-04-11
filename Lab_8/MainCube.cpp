#include "MainCube.h"
#include "windows.h"

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
    cords.x = 0;
    cords.y = 0;
    cords.z = 0;
    size = 1.0f;

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                squares[x][y][z].ChangeCords(float(x - 1)*(size/3), float(y - 1)*(size/3), float(z - 1)*(size/3));
                squares[x][y][z].Init(size);
            }
        }
    }
}

void MainCube::turnVertical(int ver, int orientation, int flag) {
    if (flag == 1) {
        if (orientation == down) {
            stackSolve.emplace_back(ver, up);
        } else {
            stackSolve.emplace_back(ver, down);
        }
    } else if (flag == 2) {
        operations.emplace_back(ver, orientation);
//        double startTime = glfwGetTime();
//        while (glfwGetTime() - startTime < 0.5) {}
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
            squares[ver][2][0].FindSide(i, move_1.sides_colors[i]);
            squares[ver][2][2].FindSide(i, move_4.sides_colors[i]);
            squares[ver][0][0].FindSide(i, move_2.sides_colors[i]);
            squares[ver][0][2].FindSide(i, move_3.sides_colors[i]);
        }
        move_1 = squares[ver][1][0], move_2 = squares[ver][0][1], move_3 = squares[ver][1][2], move_4 = squares[ver][2][1];

        for (int i = 0; i < 6; i++) {
            squares[ver][1][0].FindSide(i, move_2.sides_colors[i]);
            squares[ver][0][1].FindSide(i, move_3.sides_colors[i]);
            squares[ver][1][2].FindSide(i, move_4.sides_colors[i]);
            squares[ver][2][1].FindSide(i, move_1.sides_colors[i]);
        }
    }
    else if (orientation == up) {
        for (int i = 0; i < 6; i++) {
            squares[ver][2][0].FindSide(i, move_3.sides_colors[i]);
            squares[ver][0][2].FindSide(i, move_1.sides_colors[i]);
            squares[ver][2][2].FindSide(i, move_2.sides_colors[i]);
            squares[ver][0][0].FindSide(i, move_4.sides_colors[i]);
        }
        move_1 = squares[ver][1][0], move_2 = squares[ver][0][1], move_3 = squares[ver][1][2], move_4 = squares[ver][2][1];
        for (int i = 0; i < 6; i++) {
            squares[ver][1][0].FindSide(i, move_4.sides_colors[i]);
            squares[ver][0][1].FindSide(i, move_1.sides_colors[i]);
            squares[ver][1][2].FindSide(i, move_2.sides_colors[i]);
            squares[ver][2][1].FindSide(i, move_3.sides_colors[i]);
        }
    }

}

void MainCube::turnHorizontal(int indHor, int orientation, int flag) {
    if (flag == 1) {
        if (orientation == left) {
            stackSolve.emplace_back(indHor, right);
        } else {
            stackSolve.emplace_back(indHor, left);
        }
    } else if (flag == 2) {
        operations.emplace_back(indHor, orientation);
//        double startTime = glfwGetTime();
//        while (glfwGetTime() - startTime < 0.5) {}
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
            squares[0][indHor][2].FindSide(i, move_1.sides_colors[i]);
            squares[2][indHor][2].FindSide(i, move_2.sides_colors[i]);
            squares[2][indHor][0].FindSide(i, move_3.sides_colors[i]);
            squares[0][indHor][0].FindSide(i, move_4.sides_colors[i]);
        }
        move_1 = squares[1][indHor][0], move_2 = squares[0][indHor][1], move_3 = squares[1][indHor][2], move_4 = squares[2][indHor][1];
        for (int i = 0; i < 6; i++) {
            squares[0][indHor][1].FindSide(i,move_1.sides_colors[i]);
            squares[1][indHor][2].FindSide(i,move_2.sides_colors[i]);
            squares[2][indHor][1].FindSide(i,move_3.sides_colors[i]);
            squares[1][indHor][0].FindSide(i,move_4.sides_colors[i]);
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            squares[2][indHor][0].FindSide(i,move_1.sides_colors[i]);
            squares[2][indHor][2].FindSide(i,move_4.sides_colors[i]);
            squares[0][indHor][0].FindSide(i,move_2.sides_colors[i]);
            squares[0][indHor][2].FindSide(i,move_3.sides_colors[i]);
        }
        move_1 = squares[1][indHor][0], move_2 = squares[0][indHor][1], move_3 = squares[1][indHor][2], move_4 = squares[2][indHor][1];
        for (int i = 0; i < 6; i++) {
            squares[2][indHor][1].FindSide(i,move_1.sides_colors[i]);
            squares[1][indHor][0].FindSide(i,move_2.sides_colors[i]);
            squares[0][indHor][1].FindSide(i,move_3.sides_colors[i]);
            squares[1][indHor][2].FindSide(i,move_4.sides_colors[i]);
        }
    }

}

void MainCube::turnAround(int edge, int orientation, int flag) {

    if (flag == 1) {
        if (orientation == round_right) {
            stackSolve.emplace_back(edge, round_left);
        } else {
            stackSolve.emplace_back(edge, round_right);
        }
    } else if (flag == 2) {
        operations.emplace_back(edge, orientation);
//        double startTime = glfwGetTime();
//        while (glfwGetTime() - startTime < 0.5) {}
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
            squares[2][0][edge].FindSide(i,move_1.sides_colors[i]);
            squares[2][2][edge].FindSide(i,move_2.sides_colors[i]);
            squares[0][2][edge].FindSide(i,move_3.sides_colors[i]);
            squares[0][0][edge].FindSide(i,move_4.sides_colors[i]);
        }
        move_1 = squares[0][1][edge], move_2 = squares[1][2][edge], move_3 = squares[2][1][edge], move_4 = squares[1][0][edge];
        for (int i = 0; i < 6; i++) {
            squares[2][1][edge].FindSide(i,move_4.sides_colors[i]);
            squares[1][2][edge].FindSide(i,move_3.sides_colors[i]);
            squares[0][1][edge].FindSide(i,move_2.sides_colors[i]);
            squares[1][0][edge].FindSide(i,move_1.sides_colors[i]);
        }
    }
    else if (orientation == round_right) {
        for (int i = 0; i < 6; i++) {
            squares[0][2][edge].FindSide(i,move_1.sides_colors[i]);
            squares[2][2][edge].FindSide(i,move_4.sides_colors[i]);
            squares[2][0][edge].FindSide(i,move_3.sides_colors[i]);
            squares[0][0][edge].FindSide(i,move_2.sides_colors[i]);
        }
        move_1 = squares[0][1][edge], move_2 = squares[1][2][edge], move_3 = squares[2][1][edge], move_4 = squares[1][0][edge];
        for (int i = 0; i < 6; i++) {
            squares[1][2][edge].FindSide(i,move_1.sides_colors[i]);
            squares[2][1][edge].FindSide(i,move_2.sides_colors[i]);
            squares[1][0][edge].FindSide(i,move_3.sides_colors[i]);
            squares[0][1][edge].FindSide(i,move_4.sides_colors[i]);
        }
    }

}

void MainCube::shuffle() {
    int countOperations = 5;

    FILE* save = fopen("../OutputAndInput/input.txt", "w");
    char way, id, orientation;
    for (int i = 0; i < countOperations; i++) {
        way = rand()%3;
        id = rand()%3;
        if (way == 0) {
            orientation = rand() % 2 + 2;
            turnHorizontal(id, orientation, 1);
        }
        else if (way == 1){
            orientation = rand() % 2;
            turnVertical(id, orientation, 1);
        }
        else {
            orientation = rand() % 2 + 4;
            turnAround(id, orientation, 1);
        }
        glLoadIdentity();
        glFinish();
        std::putc(way+97,save);
        std::putc(id+97,save);
        std::putc(orientation+98,save);
    }

    std::fclose(save);
}

void MainCube::solve_with_stack() {

    auto [index, operation] = stackSolve.back();
    stackSolve.pop_back();
    double startTime = glfwGetTime();

    if (operation == up || operation == down) {
        turnVertical(index, operation, -1);
        while (glfwGetTime() - startTime < 0.5) {}
    } else if (operation == left || operation == right) {
        turnHorizontal(index, operation, -1);
        while (glfwGetTime() - startTime < 0.5) {}
    } else if (operation == round_left || operation == round_right) {
        turnAround(index, operation, -1);
        while (glfwGetTime() - startTime < 0.5) {}
    }
}

void MainCube::solve_with_algorithms() {
    set_up_centers();
//    white_cross();
}

void MainCube::show_operations_of_solving() {

    auto [index, operation] = operations.back();
    operations.pop_back();
    double startTime = glfwGetTime();

    if (operation == up || operation == down) {
        turnVertical(index, operation, -1);
        while (glfwGetTime() - startTime < 0.5) {}
    } else if (operation == left || operation == right) {
        turnHorizontal(index, operation, -1);
        while (glfwGetTime() - startTime < 0.5) {}
    } else if (operation == round_left || operation == round_right) {
        turnAround(index, operation, -1);
        while (glfwGetTime() - startTime < 0.5) {}
    }
}

void MainCube::white_cross() {
    // для верхней части, где hor = 2, надо знать 5 индекс и индекс цетра этой грани
    int counter = 0;
    for (int vertical = 0; vertical < 3; vertical++) {
        if (counter >= 4) break;
        for (int horizontal = 2; horizontal < 3; horizontal++) {
            if (counter >= 4) break;
            for (int side = 0; side < 3; side++) {
                if (counter >= 4) break;
                if (vertical ^ horizontal) {
                    char center = find_center(vertical, side);
                    if (squares[vertical][horizontal][side].sides_colors[5] == white || squares[vertical][horizontal][side].sides_colors[center] == white) {
                        // нашел кубик с белым на одной из его частей
                        ++counter;
                        if (squares[vertical][horizontal][side].sides_colors[5] == white) {
                            if (center == squares[vertical][horizontal][side].sides_colors[center]) {
                                // если у нас сверху белый и нам подошел центр
                                if (side == 0 || side == 2) {
                                    turnAround(side, round_right, 2);
                                    turnAround(side, round_right, 2);
                                } else {
                                    turnVertical(vertical, down, 2);
                                    turnVertical(vertical, down, 2);
                                }
                            } else {
                                // если центр не подошел

                                if (center == red) {
                                    if (squares[vertical][horizontal][side].sides_colors[center] == blue) {

                                        turnHorizontal(horizontal, left, 2);

                                        turnVertical(leftVert, down, 2);
                                        turnVertical(leftVert, down, 2);

                                    } else if (squares[vertical][horizontal][side].sides_colors[center] == green) {

                                        turnHorizontal(horizontal, right, 2);

                                        turnVertical(rightVert, down, 2);
                                        turnVertical(rightVert, down, 2);

                                    } else if (squares[vertical][horizontal][side].sides_colors[center] == orange) {

                                        turnHorizontal(horizontal, left, 2);
                                        turnHorizontal(horizontal, left, 2);

                                        turnAround(farAround, round_left, 2);
                                        turnAround(farAround, round_left, 2);

                                    }
                                } else if (center == blue) {
                                    if (squares[vertical][horizontal][side].sides_colors[center] == red) {

                                        turnHorizontal(horizontal, right, 2);

                                        turnAround(nearAround, round_left, 2);
                                        turnAround(nearAround, round_left, 2);

                                    } else if (squares[vertical][horizontal][side].sides_colors[center] == orange) {

                                        turnHorizontal(horizontal, left, 2);

                                        turnAround(farAround, round_left, 2);
                                        turnAround(farAround, round_left, 2);

                                    } else if (squares[vertical][horizontal][side].sides_colors[center] == green) {
                                        turnHorizontal(horizontal, left, 2);
                                        turnHorizontal(horizontal, left, 2);

                                        turnVertical(rightVert, down, 2);
                                        turnVertical(rightVert, down, 2);
                                    }
                                } else if (center == green) {
                                    if (squares[vertical][horizontal][side].sides_colors[center] == red) {

                                        turnHorizontal(horizontal, left, 2);

                                        turnAround(nearAround, round_left, 2);
                                        turnAround(nearAround, round_left, 2);

                                    } else if (squares[vertical][horizontal][side].sides_colors[center] == orange) {

                                        turnHorizontal(horizontal, right, 2);

                                        turnAround(farAround, round_left, 2);
                                        turnAround(farAround, round_left, 2);

                                    } else if (squares[vertical][horizontal][side].sides_colors[center] == blue) {
                                        turnHorizontal(horizontal, left, 2);
                                        turnHorizontal(horizontal, left, 2);

                                        turnVertical(leftVert, down, 2);
                                        turnVertical(leftVert, down, 2);
                                    }
                                } else { // center = orange
                                    if (squares[vertical][horizontal][side].sides_colors[center] == green) {

                                        turnHorizontal(horizontal, left, 2);

                                        turnVertical(rightVert, down, 2);
                                        turnVertical(rightVert, down, 2);

                                    } else if (squares[vertical][horizontal][side].sides_colors[center] == blue) {

                                        turnHorizontal(horizontal, right, 2);

                                        turnVertical(leftVert, down, 2);
                                        turnVertical(leftVert, down, 2);

                                    } else if (squares[vertical][horizontal][side].sides_colors[center] == red) {

                                        turnHorizontal(horizontal, left, 2);
                                        turnHorizontal(horizontal, left, 2);

                                        turnAround(nearAround, round_left, 2);
                                        turnAround(nearAround, round_left, 2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}

char MainCube::find_center(int ver, int side) {
    if (ver == 0) {
        return blue;
    }
    if (ver == 2) {
        return green;
    }
    if (side == 2) {
        return red;
    }
    return orange;
}

void MainCube::set_up_centers() {

    if (squares[1][1][2].sides_colors[2] != red) {
        int count = 0;
        while (squares[1][1][2].sides_colors[2] != red) {
            if (count == 3) {
                turnVertical(centralVert, down, 2);
                count = 0;
            } else {
                turnHorizontal(middleHor, left, 2);
                ++count;
            }
        }
    }

    if (squares[1][2][1].sides_colors[5] != yellow) {
        if (squares[1][2][1].sides_colors[5] == blue) {
            turnAround(centerAround, round_left, 2);
        } else if (squares[1][2][1].sides_colors[5] == green) {
            turnAround(centerAround, round_right, 2);
        } else { // white
            turnAround(centerAround, round_right, 2);
            turnAround(centerAround, round_right, 2);
        }
    }
}
