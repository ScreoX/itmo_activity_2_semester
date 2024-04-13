#include "MainCube.h"
#include "windows.h"

void MainCube::Draw(std::vector<Colors*> temp_colors, glm::mat4 MVP) {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                squares[x][y][z].Draw(temp_colors, MVP);
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
using namespace glm;

int MainCube::init() {

    if (!glfwInit()) {
        std::cout << "Failed: No glfw init";
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    screen = glfwCreateWindow(1000, 1000, "My Cube", NULL, NULL);  //создать окно

    glfwMakeContextCurrent(screen);

    Init();

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cout << "no glew init";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    colors.resize(6);

    colors[0] = addColors("../Edges/main.glslv", "../Edges/front.glslf");
    colors[1] = addColors("../Edges/main.glslv", "../Edges/left.glslf");
    colors[2] = addColors("../Edges/main.glslv", "../Edges/back.glslf");
    colors[3] = addColors("../Edges/main.glslv", "../Edges/right.glslf");
    colors[4] = addColors("../Edges/main.glslv", "../Edges/bottom.glslf");
    colors[5] = addColors("../Edges/main.glslv", "../Edges/up.glslf");

    glfwSetInputMode(screen, GLFW_STICKY_KEYS, GLFW_TRUE);
    return 0;
}

void MainCube::drawCube(Cords temp_cords) {
    glLoadIdentity();
    glFinish();
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // задний фон
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 Projection = glm::perspective(glm::radians(GLfloat(90)), 1.0f, 0.1f, 100.0f);
    glm::mat4 Camera = glm::lookAt( glm::vec3(temp_cords.x, temp_cords.y, temp_cords.z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // изначальное расположение камеры кубика
    auto Model = glm::mat4(1.0f);
    glm::mat4 MVP = Projection * Camera * Model;

    Draw(colors, MVP);
    glfwSwapBuffers(screen);
}

void MainCube::changePositions(MainCube& mainScreen) {
    Cords cords_vis = Cords(1,1,1);
    int iteration = 0;
    bool wasReleased = false;
    do {
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_ENTER) == GLFW_PRESS) {
            if (!wasReleased) {
                switch (iteration) {
                    case 0: cords_vis.x = 1, cords_vis.y = 1, cords_vis.z = 1; break;
                    case 1: cords_vis.x = 1, cords_vis.y = 1, cords_vis.z = -1; break;
                    case 2: cords_vis.x = -1, cords_vis.y = 1, cords_vis.z = -1; break;
                    case 3: cords_vis.x = -1, cords_vis.y = 1, cords_vis.z = 1; break;
                    case 4: cords_vis.x = 1, cords_vis.y = -1, cords_vis.z = 1; break;
                    case 5: cords_vis.x = -1, cords_vis.y = -1, cords_vis.z = -1; break;
                    case 6: cords_vis.x = -1, cords_vis.y = -1, cords_vis.z = 1; break;
                    case 7: cords_vis.x = 1, cords_vis.y = -1, cords_vis.z = -1; break;
                }
                iteration = (iteration + 1) % 8;
                wasReleased = true;
            }
        } else {
            wasReleased = false;
        }

        // Turning MainCube

        // [vertical][horizontal][round] - indexes

        // Vertical
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_A)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_A)) {
                mainScreen.turnVertical(leftVert,down, 1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_S)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_S)) {
                mainScreen.turnVertical(centralVert,down, 1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_D)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_D)) {
                mainScreen.turnVertical(rightVert,down, 1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_Q)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_Q)) {
                mainScreen.turnVertical(leftVert,up, 1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_W)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_W)) {
                mainScreen.turnVertical(centralVert,up, 1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_E)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_E)) {
                mainScreen.turnVertical(rightVert,up, 1);
            }
        }


        // Horizontal
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_R)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_R)) {
                mainScreen.turnHorizontal(lowHor,left, 1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_T)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_T)) {
                mainScreen.turnHorizontal(middleHor, left, 1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_Y)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_Y)) {
                mainScreen.turnHorizontal(upHor, left, 1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_F)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_F))  {
                mainScreen.turnHorizontal(lowHor,right, 1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_G)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_G)) {
                mainScreen.turnHorizontal(middleHor,right, 1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_H)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_H)) {
                mainScreen.turnHorizontal(upHor,right, 1);
            }
        }

        // Around

        if (glfwGetKey(mainScreen.screen, GLFW_KEY_U)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_U)) {
                mainScreen.turnAround(farAround,round_left, 1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_I)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_I)) {
                mainScreen.turnAround(centerAround,round_left, 1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_O)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_O)) {
                mainScreen.turnAround(nearAround,round_left, 1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_J)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_J)) {
                mainScreen.turnAround(farAround,round_right, 1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_K)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_K)) {
                mainScreen.turnAround(centerAround,round_right, 1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_L)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_L)) {
                mainScreen.turnAround(nearAround,round_right, 1);
            }
        }



        //Shuffle
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_TAB)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_TAB)) {
                mainScreen.shuffle();
            }
        }
        // Solve with stack
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_SPACE)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_SPACE)) {

                while(!mainScreen.stackSolve.empty()) {
                    mainScreen.solve_with_stack();
                    mainScreen.drawCube(cords_vis);
                }
            }
        }

        // Solve with algorithms
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_M)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_M)) {

                mainScreen.solve_with_algorithms();

            }
        }

        mainScreen.drawCube(cords_vis);
        glfwPollEvents();
    }

    while(glfwGetKey(mainScreen.screen, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(mainScreen.screen) == 0);
    glfwTerminate();
}










void MainCube::turnVertical(int ver, int orientation, int flag) {

    double startTime = glfwGetTime();
    if (flag == 3) {
        while (glfwGetTime() - startTime < 0.1) {}
    } else {
        while (glfwGetTime() - startTime < 0.05) {}
    }

    if (flag == 3) {
        if (orientation == down) {
            stackSolve.emplace_back(ver, up);
        } else {
            stackSolve.emplace_back(ver, down);
        }
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
        drawCube(cordsVisual);
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
        drawCube(cordsVisual);
    }

}

void MainCube::turnHorizontal(int indHor, int orientation, int flag) {
    double startTime = glfwGetTime();
    if (flag == 3) {
        while (glfwGetTime() - startTime < 0.1) {}
    } else {
        while (glfwGetTime() - startTime < 0.05) {}
    }

    if (flag == 3) {
        if (orientation == left) {
            stackSolve.emplace_back(indHor, right);
        } else {
            stackSolve.emplace_back(indHor, left);
        }
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
        drawCube(cordsVisual);
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
        drawCube(cordsVisual);
    }

}

void MainCube::turnAround(int edge, int orientation, int flag) {

    double startTime = glfwGetTime();
    if (flag == 3) {
        while (glfwGetTime() - startTime < 0.1) {}
    } else {
        while (glfwGetTime() - startTime < 0.05) {}
    }

    if (flag == 3) {
        if (orientation == round_right) {
            stackSolve.emplace_back(edge, round_left);
        } else {
            stackSolve.emplace_back(edge, round_right);
        }
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
        drawCube(cordsVisual);
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
        drawCube(cordsVisual);
    }

}

void MainCube::shuffle() {
    int countOperations = 12;

    FILE *save = fopen("../OutputAndInput/input.txt", "w");
    char way, id, orientation;
    for (int i = 0; i < countOperations; i++) {
        way = rand() % 3;
        id = rand() % 3;
        if (way == 0) {
            orientation = rand() % 2 + 2;
            turnHorizontal(id, orientation, 3);
            drawCube(cordsVisual);
        } else if (way == 1) {
            orientation = rand() % 2;
            turnVertical(id, orientation, 3);
            drawCube(cordsVisual);
        } else {
            orientation = rand() % 2 + 4;
            turnAround(id, orientation, 3);
            drawCube(cordsVisual);
        }
        glLoadIdentity();
        glFinish();
        std::putc(way + 97, save);
        std::putc(id + 97, save);
        std::putc(orientation + 98, save);

        std::fclose(save);
    }
}

void MainCube::solve_with_stack() {

    auto [index, operation] = stackSolve.back();
    stackSolve.pop_back();
    double startTime = glfwGetTime();

    if (operation == up || operation == down) {
        turnVertical(index, operation, -1);
    } else if (operation == left || operation == right) {
        turnHorizontal(index, operation, -1);
    } else if (operation == round_left || operation == round_right) {
        turnAround(index, operation, -1);
    }
}

void MainCube::check_centers(int round) {
    complete_colors();
    white_cross();
    for (int i = 0; i < 4; i++) {

        if (!check_white_cross[i]) {

            if (round == 0) {// red
                turnAround(nearAround, round_right, 2);
                if (!check_white_cross[red]) {
                    turnAround(nearAround, round_right, 2);
                    complete_colors();
                }
                if (checkWhiteCross()) {
                    break;
                }
                turnHorizontal(upHor, left, 2);
                turnAround(nearAround, round_left, 2);

            } else if (round == 1) { // blue
                turnVertical(leftVert, down, 2);
                if (!check_white_cross[blue]) {
                    turnVertical(leftVert, down, 2);
                    complete_colors();
                }
                if (checkWhiteCross()) {
                    break;
                }
                turnHorizontal(upHor, left, 2);
                turnVertical(leftVert, up, 2);
            } else if (round == 2) { // orange
                turnAround(farAround, round_left, 2);
                if (!check_white_cross[orange]) {
                    turnAround(farAround, round_left, 2);
                    complete_colors();
                }
                if (checkWhiteCross()) {
                    break;
                }
                turnHorizontal(upHor, left, 2);
                turnAround(farAround, round_right, 2);
            } else { // round = 3 green
                turnVertical(rightVert, up, 2);
                if (!check_white_cross[green]) {
                    turnVertical(rightVert, up, 2);
                    complete_colors();
                }
                if (checkWhiteCross()) {
                    break;
                }
                turnHorizontal(upHor, left, 2);
                turnVertical(rightVert, down, 2);
            }
            break;
        }
    }
}

void MainCube::solve_with_algorithms() {
    set_up_centers(); // устанавливаю для удобства центры

    int round = 0;
    while (!checkWhiteCross()) { // надо будет проверить еще раз
        check_centers(round);
        round = (round + 1) % 4;
    }
    double startTime = glfwGetTime();
    while (glfwGetTime() - startTime < 2) {}


    for (int i = 0; i < 4; i++) { // возможно нужно побольше итераций хз почему :(
        white_corners();
    }

    startTime = glfwGetTime();
    while (glfwGetTime() - startTime < 2) {}

    put_white_corners();

    startTime = glfwGetTime();
    while (glfwGetTime() - startTime < 2) {}

    side_mini_cubes();

    startTime = glfwGetTime();
    while (glfwGetTime() - startTime < 2) {}

    put_side_mini_cubes();

    startTime = glfwGetTime();
    while (glfwGetTime() - startTime < 2) {}

    make_yellow_cross();

    startTime = glfwGetTime();
    while (glfwGetTime() - startTime < 2) {}

    top_layer_centers();

    startTime = glfwGetTime();
    while (glfwGetTime() - startTime < 2) {}

    make_right_position_for_yellow_cornerns();

}

void MainCube::white_cross() { // нужно учесть, что я не нарушаю уже стоящие центры при поворотах
    // для верхней части, где hor = 2, надо знать 5 индекс и индекс цетра этой грани
    for (int vertical = 0; vertical < 3; vertical++) {
        for (int side = 0; side < 3; side++) {
            if ((vertical == 0 && side == 0) || (vertical == 2 && side == 2) || (vertical == 0 && side == 2) || (vertical == 2 && side == 0) || (vertical == 1 && side == 1)) {
                break;
            }
            char center = find_center(vertical, side);

            if (squares[vertical][upHor][side].sides_colors[5] == white || squares[vertical][upHor][side].sides_colors[center] == white) {
                // нашел кубик с белым на одной из его частей
                if (squares[vertical][upHor][side].sides_colors[5] == white) {
                    if (center == squares[vertical][upHor][side].sides_colors[center]) {
                        // если у нас сверху белый и нам подошел центр
                        if (side == 0 || side == 2) {
                            turnAround(side, round_right, 2);
                            turnAround(side, round_right, 2);
                        } else {
                            turnVertical(vertical, down, 2);
                            turnVertical(vertical, down, 2);
                        }
                        check_white_cross[squares[vertical][upHor][side].sides_colors[center]] = true;
                    } else {
                        // если центр не подошел и белый сверху

                        if (center == red) { // надо будет заменить hor на uphor
                            if (squares[vertical][upHor][side].sides_colors[center] == blue) {

                                turnHorizontal(upHor, left, 2);

                                turnVertical(leftVert, down, 2);
                                turnVertical(leftVert, down, 2);

                            } else if (squares[vertical][upHor][side].sides_colors[center] == green) {

                                turnHorizontal(upHor, right, 2);

                                turnVertical(rightVert, down, 2);
                                turnVertical(rightVert, down, 2);

                            } else if (squares[vertical][upHor][side].sides_colors[center] == orange) {

                                turnHorizontal(upHor, left, 2);
                                turnHorizontal(upHor, left, 2);

                                turnAround(farAround, round_left, 2);
                                turnAround(farAround, round_left, 2);

                            }
                        } else if (center == blue) {
                            if (squares[vertical][upHor][side].sides_colors[center] == red) {

                                turnHorizontal(upHor, right, 2);

                                turnAround(nearAround, round_left, 2);
                                turnAround(nearAround, round_left, 2);

                            } else if (squares[vertical][upHor][side].sides_colors[center] == orange) {

                                turnHorizontal(upHor, left, 2);

                                turnAround(farAround, round_left, 2);
                                turnAround(farAround, round_left, 2);

                            } else if (squares[vertical][upHor][side].sides_colors[center] == green) {
                                turnHorizontal(upHor, left, 2);
                                turnHorizontal(upHor, left, 2);

                                turnVertical(rightVert, down, 2);
                                turnVertical(rightVert, down, 2);
                            }
                        } else if (center == green) {
                            if (squares[vertical][upHor][side].sides_colors[center] == red) {

                                turnHorizontal(upHor, left, 2);

                                turnAround(nearAround, round_left, 2);
                                turnAround(nearAround, round_left, 2);

                            } else if (squares[vertical][upHor][side].sides_colors[center] == orange) {

                                turnHorizontal(upHor, right, 2);

                                turnAround(farAround, round_left, 2);
                                turnAround(farAround, round_left, 2);

                            } else if (squares[vertical][upHor][side].sides_colors[center] == blue) {
                                turnHorizontal(upHor, left, 2);
                                turnHorizontal(upHor, left, 2);

                                turnVertical(leftVert, down, 2);
                                turnVertical(leftVert, down, 2);
                            }
                        } else { // center = orange
                            if (squares[vertical][upHor][side].sides_colors[center] == green) {

                                turnHorizontal(upHor, left, 2);

                                turnVertical(rightVert, down, 2);
                                turnVertical(rightVert, down, 2);

                            } else if (squares[vertical][upHor][side].sides_colors[center] == blue) {

                                turnHorizontal(upHor, right, 2);

                                turnVertical(leftVert, down, 2);
                                turnVertical(leftVert, down, 2);

                            } else if (squares[vertical][upHor][side].sides_colors[center] == red) {

                                turnHorizontal(upHor, left, 2);
                                turnHorizontal(upHor, left, 2);

                                turnAround(nearAround, round_left, 2);
                                turnAround(nearAround, round_left, 2);
                            }
                        }
                        check_white_cross[squares[vertical][upHor][side].sides_colors[center]] = true;
                    }
                } else { //белый смотрит не наверх, а другой цвет на нас
                    char color_above_white = squares[vertical][upHor][side].sides_colors[5];
                    char temp_center = find_center(vertical, side);

                    if (temp_center == red) {
                        if (color_above_white == blue) {

                            turnAround(nearAround, round_left, 2);

                            turnVertical(leftVert, down, 2);

                            // вернуть прошлую сторону обратно
                            turnAround(nearAround, round_right, 2);

                        } else if (color_above_white == green) {

                            turnAround(nearAround, round_right, 2);

                            turnVertical(rightVert, down, 2);

                            // вернуть прошлую сторону обратно
                            turnAround(nearAround, round_left, 2);
                        } else if (color_above_white == orange) { // orange
                            turnHorizontal(upHor, left, 2);
                            turnVertical(leftVert, up, 2);
                            turnAround(farAround, round_left, 2);

                            // вернуть прошлую сторону обратно
                            turnVertical(leftVert, down, 2);
                        } else if (color_above_white == red) { //red
                            turnHorizontal(upHor, left, 2);
                            turnVertical(leftVert, down, 2);
                            turnAround(nearAround, round_left, 2); // need to check

                            // вернуть прошлую сторону обратно
                            turnVertical(leftVert, up, 2);
                        }
                    } else if (temp_center == blue) {
                        if (color_above_white == red) {

                            turnVertical(leftVert, down, 2);
                            turnAround(nearAround, round_left, 2);

                            // вернуть прошлую сторону обратно
                            turnVertical(leftVert, up, 2);


                        } else if (color_above_white == orange) {

                            turnVertical(leftVert, up, 2);
                            turnAround(farAround, round_left, 2);

                            // вернуть прошлую сторону обратно
                            turnVertical(leftVert, down, 2);

                        } else if (color_above_white == green) {

                            turnHorizontal(upHor, right, 2);
                            turnAround(nearAround, round_right, 2);
                            turnVertical(rightVert, down, 2);

                            // вернуть прошлую сторону обратно
                            turnAround(nearAround, round_left, 2);

                        } else if (color_above_white == blue) { //blue
                            turnHorizontal(upHor, right, 2);
                            turnAround(nearAround, round_left, 2);
                            turnVertical(leftVert, down, 2);

                            // вернуть прошлую сторону обратно
                            turnAround(nearAround, round_right, 2);
                        }
                    } else if (temp_center == green) {
                        if (color_above_white == red) {

                            turnVertical(rightVert, down, 2);
                            turnAround(nearAround, round_right, 2);

                            // вернуть прошлую сторону обратно
                            turnVertical(rightVert, up, 2);

                        } else if (color_above_white == orange) {

                            turnVertical(rightVert, up, 2);
                            turnAround(farAround, round_right, 2);

                            // вернуть прошлую сторону обратно
                            turnVertical(rightVert, down, 2);

                        } else if (color_above_white == blue) {
                            turnHorizontal(upHor, left, 2);
                            turnAround(nearAround, round_left, 2);
                            turnVertical(leftVert, down, 2);

                            // вернуть прошлую сторону обратно
                            turnAround(nearAround, round_right, 2);

                        } else if (color_above_white == green) { // green
                            turnHorizontal(upHor, left, 2);
                            turnAround(nearAround, round_right, 2);
                            turnVertical(rightVert, down, 2);

                            // вернуть прошлую сторону обратно
                            turnAround(nearAround, round_left, 2);
                        }
                    } else if (temp_center == orange) { // orange
                        if (color_above_white == blue) {
                            turnAround(farAround, round_left, 2);
                            turnVertical(leftVert, up, 2);

                            // вернуть прошлую сторону обратно
                            turnAround(farAround, round_right, 2);

                        } else if (color_above_white == green) {
                            turnAround(farAround, round_right, 2);
                            turnVertical(rightVert, up, 2);

                            // вернуть прошлую сторону обратно
                            turnAround(farAround, round_left, 2);
                        } else if (color_above_white == red) {
                            turnHorizontal(upHor, left, 2);
                            turnVertical(rightVert, down, 2);
                            turnAround(nearAround, round_right, 2);

                            // вернуть прошлую сторону обратно
                            turnVertical(rightVert, up, 2);
                        } else if (color_above_white == orange) { // orange
                            turnHorizontal(upHor, left, 2);
                            turnVertical(rightVert, up, 2);
                            turnAround(farAround, round_right, 2);

                            // вернуть прошлую сторону обратно
                            turnVertical(rightVert, down, 2);
                        }
                    }
                    check_white_cross[color_above_white] = true;
                }
            }
        }
    }
}

void MainCube::put_white_corners() {
    for (int i = 0; i < 4; i++) { // синий красный
        if (squares[0][2][2].sides_colors[red] == red || squares[0][2][2].sides_colors[blue] == red || squares[0][2][2].sides_colors[yellow] == red) {
            if (squares[0][2][2].sides_colors[red] == blue || squares[0][2][2].sides_colors[blue] == blue || squares[0][2][2].sides_colors[yellow] == blue) {
                if (squares[0][2][2].sides_colors[blue] == white) {
                    pifpaf_red_white_blue();
                    pifpaf_red_white_blue();
                    pifpaf_red_white_blue();
                    pifpaf_red_white_blue();
                    pifpaf_red_white_blue();
                } else if (squares[0][2][2].sides_colors[yellow] == white) {
                    pifpaf_red_white_blue();
                    pifpaf_red_white_blue();
                    pifpaf_red_white_blue();
                } else {
                    pifpaf_red_white_blue();
                }
                break;
            } else {
                turnHorizontal(upHor, right, 2);
            }
        } else {
            turnHorizontal(upHor, right, 2);
        }
    }
    for (int i = 0; i < 4; i++) { // красный зеленый
        if (squares[2][2][2].sides_colors[red] == red || squares[2][2][2].sides_colors[green] == red || squares[2][2][2].sides_colors[yellow] == red) {
            if (squares[2][2][2].sides_colors[red] == green || squares[2][2][2].sides_colors[green] == green || squares[2][2][2].sides_colors[yellow] == green) {
                if (squares[2][2][2].sides_colors[red] == white || squares[2][2][2].sides_colors[green] == white || squares[2][2][2].sides_colors[yellow] == white) {
                    if (squares[2][2][2].sides_colors[red] == white) {
                        pifpaf_red_white_green();
                        pifpaf_red_white_green();
                        pifpaf_red_white_green();
                        pifpaf_red_white_green();
                        pifpaf_red_white_green();
                    } else if (squares[2][2][2].sides_colors[yellow] == white) {
                        pifpaf_red_white_green();
                        pifpaf_red_white_green();
                        pifpaf_red_white_green();
                    } else {
                        pifpaf_red_white_green();
                    }
                    break;
                } else {
                    turnHorizontal(upHor, right, 2);
                }
            } else {
                turnHorizontal(upHor, right, 2);
            }
        } else {
            turnHorizontal(upHor, right, 2);
        }
    }
    for (int i = 0; i < 4; i++) { // синий оранжевый
        if (squares[0][2][0].sides_colors[orange] == blue || squares[0][2][0].sides_colors[blue] == blue || squares[0][2][0].sides_colors[yellow] == blue) {
            if (squares[0][2][0].sides_colors[orange] == orange || squares[0][2][0].sides_colors[blue] == orange || squares[0][2][0].sides_colors[yellow] == orange) {
                if (squares[0][2][0].sides_colors[orange] == white || squares[0][2][0].sides_colors[blue] == white || squares[0][2][0].sides_colors[yellow] == white) {
                    if (squares[0][2][0].sides_colors[orange] == white) {
                        pifpaf_orange_white_blue();
                        pifpaf_orange_white_blue();
                        pifpaf_orange_white_blue();
                        pifpaf_orange_white_blue();
                        pifpaf_orange_white_blue();
                    } else if (squares[0][2][0].sides_colors[yellow] == white) {
                        pifpaf_orange_white_blue();
                        pifpaf_orange_white_blue();
                        pifpaf_orange_white_blue();
                    } else {
                        pifpaf_orange_white_blue();
                    }
                    break;
                } else {
                    turnHorizontal(upHor, right, 2);
                }
            } else {
                turnHorizontal(upHor, right, 2);
            }
        } else {
            turnHorizontal(upHor, right, 2);
        }
    }
    for (int i = 0; i < 4; i++) { // зеленый оранжевый
        if (squares[2][2][0].sides_colors[green] == green || squares[2][2][0].sides_colors[orange] == green || squares[2][2][0].sides_colors[yellow] == green) {
            if (squares[2][2][0].sides_colors[green] == orange || squares[2][2][0].sides_colors[orange] == orange || squares[2][2][0].sides_colors[yellow] == orange) {
                if (squares[2][2][0].sides_colors[green] == white || squares[2][2][0].sides_colors[orange] == white || squares[2][2][0].sides_colors[yellow] == white) {
                    if (squares[2][2][0].sides_colors[green] == white) {
                        pifpaf_orange_white_green();
                        pifpaf_orange_white_green();
                        pifpaf_orange_white_green();
                        pifpaf_orange_white_green();
                        pifpaf_orange_white_green();
                    } else if (squares[2][2][0].sides_colors[yellow] == white) {
                        pifpaf_orange_white_green();
                        pifpaf_orange_white_green();
                        pifpaf_orange_white_green();
                    } else {
                        pifpaf_orange_white_green();
                    }
                    break;
                } else {
                    turnHorizontal(upHor, right, 2);
                }
            } else {
                turnHorizontal(upHor, right, 2);
            }
        } else {
            turnHorizontal(upHor, right, 2);
        }
    }
}

void MainCube::white_corners() {
    // красный зеленый
    for (int i = 0; i < 3; i++) {
        if (!(squares[2][2][2].sides_colors[red] == white || squares[2][2][2].sides_colors[green] == white ||
              squares[2][2][2].sides_colors[yellow] == white)) {
            if (squares[2][0][2].sides_colors[red] == white || squares[2][0][2].sides_colors[green] == white ||
                squares[2][0][2].sides_colors[white] == white) {
                pifpaf_red_white_green();
                check_white_corners[0] = true;
                break;
            } else {
                turnHorizontal(upHor, right, 2);
            }
        }
    }
    // красный синий
    for (int i = 0; i < 3; i++) {
        if (!(squares[0][2][2].sides_colors[red] == white || squares[0][2][2].sides_colors[blue] == white ||
              squares[0][2][2].sides_colors[yellow] == white)) {
            if (squares[0][0][2].sides_colors[red] == white || squares[0][0][2].sides_colors[blue] == white ||
                squares[0][0][2].sides_colors[white] == white) {
                pifpaf_red_white_blue();
                check_white_corners[2] = true;
                break;
            } else {
                turnHorizontal(upHor, right, 2);
            }
        }
    }
    // зеленый оранжевый
    for (int i = 0; i < 3; i++) {
        if (!(squares[2][2][0].sides_colors[orange] == white || squares[2][2][0].sides_colors[green] == white ||
              squares[2][2][0].sides_colors[yellow] == white)) {
            if (squares[2][0][0].sides_colors[orange] == white || squares[2][0][0].sides_colors[green] == white ||
                squares[2][0][0].sides_colors[white] == white) {
                pifpaf_orange_white_green();
                check_white_corners[1] = true;
                break;
            } else {
                turnHorizontal(upHor, right, 2);
            }
        }
    }
    // синий оранжевый
    for (int i = 0; i < 4; i++) {
        if (!(squares[0][2][0].sides_colors[blue] == white || squares[0][2][0].sides_colors[orange] == white ||
              squares[0][2][0].sides_colors[yellow] == white)) {
            if (squares[0][0][0].sides_colors[blue] == white || squares[0][0][0].sides_colors[orange] == white ||
                squares[0][0][0].sides_colors[white] == white) {
                pifpaf_orange_white_blue();
                check_white_corners[3] = true;
                break;
            } else {
                turnHorizontal(upHor, right, 2);
            }
        }
    }
}

void MainCube::side_mini_cubes() {
    // красный зеленый
    for (int vert = 0; vert < 4; vert++) {
        for (int side = 0; side < 4; side++) {
            if (!(squares[2][1][2].sides_colors[red] == yellow || squares[2][1][2].sides_colors[green] == yellow)) {
                if (squares[1][2][2].sides_colors[red] == yellow || squares[1][2][2].sides_colors[yellow] == yellow) {
                    comb_red_green();
                } else {
                    turnHorizontal(upHor, right, 2);
                }
            } else {
                break;
            }
        }
    }

    for (int vert = 0; vert < 4; vert++) { // красный синий
        for (int side = 0; side < 4; side++) {
            if (!(squares[0][1][2].sides_colors[red] == yellow || squares[0][1][2].sides_colors[blue] == yellow)) {
                if (squares[1][2][2].sides_colors[red] == yellow || squares[1][2][2].sides_colors[yellow] == yellow) {
                    comb_red_blue();
                } else {
                    turnHorizontal(upHor, right, 2);
                }
            } else {
                break;
            }
        }
    }

    for (int vert = 0; vert < 4; vert++) { //  оранжевый синий
        for (int side = 0; side < 4; side++) {
            if (!(squares[0][1][0].sides_colors[orange] == yellow || squares[0][1][0].sides_colors[blue] == yellow)) {
                if (squares[1][2][0].sides_colors[orange] == yellow || squares[1][2][0].sides_colors[yellow] == yellow) {
                    comb_orange_blue();
                } else {
                    turnHorizontal(upHor, right, 2);
                }
            } else {
                break;
            }
        }
    }

    for (int vert = 0; vert < 4; vert++) { // оранжевый зеленый
        for (int side = 0; side < 4; side++) {
            if (!(squares[2][1][0].sides_colors[orange] == yellow || squares[2][1][0].sides_colors[green] == yellow)) {
                if (squares[1][2][0].sides_colors[orange] == yellow || squares[1][2][0].sides_colors[yellow] == yellow) {
                    comb_orange_green();
                } else {
                    turnHorizontal(upHor, right, 2);
                }
            } else {
                break;
            }
        }
    }
}

void MainCube::put_side_mini_cubes() {
    // зеленый красный
    for (int i = 0; i < 4; i++) {
        if (squares[1][2][2].sides_colors[red] == red && squares[1][2][2].sides_colors[yellow] == green) {
            comb_red_green();
            break;
        } else if (squares[1][2][2].sides_colors[red] == green && squares[1][2][2].sides_colors[yellow] == red) {
            turnHorizontal(upHor, right, 2);
            comb_green_red();
            break;
        } else {
            turnHorizontal(upHor, right, 2);
        }
    }

    // красный синий
    for (int i = 0; i < 4; i++) {
        if (squares[1][2][2].sides_colors[red] == red && squares[1][2][2].sides_colors[yellow] == blue) {
            comb_red_blue();
            break;
        } else if (squares[1][2][2].sides_colors[red] == blue && squares[1][2][2].sides_colors[yellow] == red) {
            turnHorizontal(upHor, left, 2);
            comb_blue_red();
            break;
        } else {
            turnHorizontal(upHor, right, 2);
        }
    }

    // оранжевый зеленый
    for (int i = 0; i < 4; i++) {
        if (squares[1][2][0].sides_colors[orange] == orange && squares[1][2][0].sides_colors[yellow] == green) {
            comb_orange_green();
            break;
        } else if (squares[1][2][0].sides_colors[orange] == green && squares[1][2][0].sides_colors[yellow] == orange) {
            turnHorizontal(upHor, left, 2);
            comb_green_orange();
            break;
        } else {
            turnHorizontal(upHor, right, 2);
        }
    }

    // оранжевый синий
    for (int i = 0; i < 4; i++) {
        if (squares[1][2][0].sides_colors[orange] == orange && squares[1][2][0].sides_colors[yellow] == blue) {
            comb_orange_blue();
            break;
        } else if (squares[1][2][0].sides_colors[orange] == blue && squares[1][2][0].sides_colors[yellow] == orange) {
            turnHorizontal(upHor, right, 2);
            comb_blue_orange();
            break;
        } else {
            turnHorizontal(upHor, right, 2);
        }
    }
}

void MainCube::make_yellow_cross() {
    // Существует три вариант: полоса, птичка, крест
    // Проверим какой сейчас случай

    // проверка на крест
    if (squares[0][2][1].sides_colors[yellow] == yellow && squares[1][2][0].sides_colors[yellow] == yellow
        && squares[2][2][1].sides_colors[yellow] == yellow) {
        // ничего делать не надо
    } else if (squares[0][2][1].sides_colors[yellow] == yellow && squares[2][2][1].sides_colors[yellow] == yellow ||
               squares[1][2][2].sides_colors[yellow] == yellow && squares[1][2][0].sides_colors[yellow] == yellow) { // проверяем линию
        if (squares[1][2][2].sides_colors[yellow] == yellow && squares[1][2][0].sides_colors[yellow] == yellow) {
            turnHorizontal(upHor, left, 2);
        }

        change_positions_of_up_layer_for_yellow_centers();

    } else if (squares[0][2][1].sides_colors[yellow] != yellow && squares[1][2][0].sides_colors[yellow] != yellow && squares[2][2][1].sides_colors[yellow] != yellow) {
        change_positions_of_up_layer_for_yellow_centers();
        while (!(squares[0][2][1].sides_colors[yellow] == yellow && squares[1][2][0].sides_colors[yellow] == yellow)) {
            turnHorizontal(upHor, left, 2);
        }
        change_positions_of_up_layer_for_yellow_centers();
        change_positions_of_up_layer_for_yellow_centers();
    } else { // птичка
        while (!(squares[0][2][1].sides_colors[yellow] == yellow && squares[1][2][0].sides_colors[yellow] == yellow)) {
            turnHorizontal(upHor, left, 2);
        }

        change_positions_of_up_layer_for_yellow_centers();
        change_positions_of_up_layer_for_yellow_centers();
    }
}

void MainCube::top_layer_centers() {
    // смотрим какой у нас вариант на 3 слое:
    // 1) стоят два цвета напротив друг друга (зеленый - синий или красный - оранжевый)
    // 2) стоят рядом

    while (squares[0][2][1].sides_colors[blue] != blue) {
        turnHorizontal(upHor, right, 2);
    }

    // Проверяем какой это вариант

    if (squares[0][2][1].sides_colors[blue] == blue && squares[2][2][1].sides_colors[green] == green) {
        // да, это первый вариант
        turn_red_side();
        make_right_positions_before_last_step();
        if (squares[1][2][2].sides_colors[red] == red) {
            if (squares[0][2][1].sides_colors[blue] == blue) {
                turn_orange_side();
            } else { // another = green
                turn_blue_side();
            }
        } else { // orange
            if (squares[0][2][1].sides_colors[blue] == blue) {
                turn_green_side();
            } else { // green
                turn_red_side();
            }
        }
    } else { // нет, это второй вариант
        make_right_positions_before_last_step();
        if (squares[1][2][2].sides_colors[red] == red) {
            if (squares[0][2][1].sides_colors[blue] == blue) {
                turn_orange_side();
            } else { // another = green
                turn_blue_side();
            }
        } else { // orange
            if (squares[0][2][1].sides_colors[blue] == blue) {
                turn_green_side();
            } else { // green
                turn_red_side();
            }
        }
    }

    while (squares[0][2][1].sides_colors[blue] != blue) {
        turnHorizontal(upHor, right, 2);
    }

}

void MainCube::make_right_position_for_yellow_cornerns() {
    std::vector<bool> check_yellow_corners(4, false);
    // 0 - красный синий
    // 1 - красный зеленый
    // 2 - зеленый оранжевый
    // 3 - синий оранжевый

    int right_positions = 0;

    while (right_positions != 4) {

        check_yellow_corners.assign(4, false);

        // Проверяем положения углов (не смотрим на их ориентацию)
        if (squares[0][2][2].sides_colors[red] == red || squares[0][2][2].sides_colors[blue] == red || squares[0][2][2].sides_colors[yellow] == red) {
            if (squares[0][2][2].sides_colors[red] == blue || squares[0][2][2].sides_colors[blue] == blue || squares[0][2][2].sides_colors[yellow] == blue) {
                check_yellow_corners[0] = true;
            }
        }
        if (squares[2][2][2].sides_colors[red] == red || squares[2][2][2].sides_colors[green] == red || squares[2][2][2].sides_colors[yellow] == red) {
            if (squares[2][2][2].sides_colors[red] == green || squares[2][2][2].sides_colors[green] == green || squares[2][2][2].sides_colors[yellow] == green) {
                check_yellow_corners[1] = true;
            }
        }
        if (squares[2][2][0].sides_colors[orange] == green || squares[2][2][0].sides_colors[green] == green || squares[2][2][0].sides_colors[yellow] == green) {
            if (squares[2][2][0].sides_colors[orange] == orange || squares[2][2][0].sides_colors[green] == orange || squares[2][2][0].sides_colors[yellow] == orange) {
                check_yellow_corners[2] = true;
            }
        }
        if (squares[0][2][0].sides_colors[orange] == orange || squares[0][2][0].sides_colors[blue] == orange || squares[0][2][0].sides_colors[yellow] == orange) {
            if (squares[0][2][0].sides_colors[orange] == blue || squares[0][2][0].sides_colors[blue] == blue || squares[0][2][0].sides_colors[yellow] == blue) {
                check_yellow_corners[3] = true;
            }
        }

        right_positions = 0;

        int save_index_if_only_one_has_right_position = 0;
        for (int i = 0; i < 4; i++) {
            if (check_yellow_corners[i]) {
                ++right_positions;
                save_index_if_only_one_has_right_position = i;
            }
        }

        if (right_positions == 1) {
            if (save_index_if_only_one_has_right_position == 0) {
                put_corners_if_red_blue();
            } else if (save_index_if_only_one_has_right_position == 1) {
                put_corners_if_red_green();
            } else if (save_index_if_only_one_has_right_position == 2) {
                put_corners_if_orange_green();
            } else {
                put_corners_if_orange_blue();
            }
            right_positions = 0;

            if (squares[0][2][2].sides_colors[red] == red || squares[0][2][2].sides_colors[blue] == red || squares[0][2][2].sides_colors[yellow] == red) {
                if (squares[0][2][2].sides_colors[red] == blue || squares[0][2][2].sides_colors[blue] == blue || squares[0][2][2].sides_colors[yellow] == blue) {
                    check_yellow_corners[0] = true;
                }
            }
            if (squares[2][2][2].sides_colors[red] == red || squares[2][2][2].sides_colors[green] == red || squares[2][2][2].sides_colors[yellow] == red) {
                if (squares[2][2][2].sides_colors[red] == green || squares[2][2][2].sides_colors[green] == green || squares[2][2][2].sides_colors[yellow] == green) {
                    check_yellow_corners[1] = true;
                }
            }
            if (squares[2][2][0].sides_colors[orange] == green || squares[2][2][0].sides_colors[green] == green || squares[2][2][0].sides_colors[yellow] == green) {
                if (squares[2][2][0].sides_colors[orange] == orange || squares[2][2][0].sides_colors[green] == orange || squares[2][2][0].sides_colors[yellow] == orange) {
                    check_yellow_corners[2] = true;
                }
            }
            if (squares[0][2][0].sides_colors[orange] == orange || squares[0][2][0].sides_colors[blue] == orange || squares[0][2][0].sides_colors[yellow] == orange) {
                if (squares[0][2][0].sides_colors[orange] == blue || squares[0][2][0].sides_colors[blue] == blue || squares[0][2][0].sides_colors[yellow] == blue) {
                    check_yellow_corners[3] = true;
                }
            }

            for (int i = 0; i < 4; i++) {
                if (check_yellow_corners[i]) {
                    ++right_positions;
                    save_index_if_only_one_has_right_position = i;
                }
            }
        }
        if (right_positions == 0) {
            put_corners_if_orange_green();
        }
    }

    check_yellow_corners.assign(4, false);
    if (squares[0][2][2].sides_colors[yellow] == yellow) {
        check_yellow_corners[0] = true;
    }
    if (squares[2][2][2].sides_colors[yellow] == yellow) {
        check_yellow_corners[1] = true;
    }
    if (squares[2][2][0].sides_colors[yellow] == yellow) {
        check_yellow_corners[2] = true;
    }
    if (squares[0][2][0].sides_colors[yellow] == yellow) {
        check_yellow_corners[3] = true;
    }

    if (!check_yellow_corners[0]) {
        if (squares[0][2][2].sides_colors[red] == yellow) {
            pifpaf_for_set_up_yellow_cornerns();
            pifpaf_for_set_up_yellow_cornerns();
            pifpaf_for_set_up_yellow_cornerns();
            pifpaf_for_set_up_yellow_cornerns();
        } else if (squares[0][2][2].sides_colors[blue] == yellow) {
            pifpaf_for_set_up_yellow_cornerns();
            pifpaf_for_set_up_yellow_cornerns();
        }
    }
    turnHorizontal(upHor, left, 2);

    if (!check_yellow_corners[1]) {
        if (squares[0][2][2].sides_colors[red] == yellow) {
            pifpaf_for_set_up_yellow_cornerns();
            pifpaf_for_set_up_yellow_cornerns();
            pifpaf_for_set_up_yellow_cornerns();
            pifpaf_for_set_up_yellow_cornerns();
        } else if (squares[0][2][2].sides_colors[blue] == yellow) {
            pifpaf_for_set_up_yellow_cornerns();
            pifpaf_for_set_up_yellow_cornerns();
        }
    }
    turnHorizontal(upHor, left, 2);

    if (!check_yellow_corners[2]) {
        if (squares[0][2][2].sides_colors[red] == yellow) {
            pifpaf_for_set_up_yellow_cornerns();
            pifpaf_for_set_up_yellow_cornerns();
            pifpaf_for_set_up_yellow_cornerns();
            pifpaf_for_set_up_yellow_cornerns();
        } else if (squares[0][2][2].sides_colors[blue] == yellow) {
            pifpaf_for_set_up_yellow_cornerns();
            pifpaf_for_set_up_yellow_cornerns();
        }
    }
    turnHorizontal(upHor, left, 2);

    if (!check_yellow_corners[3]) {
        if (squares[0][2][2].sides_colors[red] == yellow) {
            pifpaf_for_set_up_yellow_cornerns();
            pifpaf_for_set_up_yellow_cornerns();
            pifpaf_for_set_up_yellow_cornerns();
            pifpaf_for_set_up_yellow_cornerns();
        } else if (squares[0][2][2].sides_colors[blue] == yellow) {
            pifpaf_for_set_up_yellow_cornerns();
            pifpaf_for_set_up_yellow_cornerns();
        }
    }
    turnHorizontal(upHor, left, 2);
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




bool MainCube::checkWhiteCross() {
    for (int i = 0; i < 4; i++) {
        if (!check_white_cross[i]) {
            return false;
        }
    }
    return true;
}

void MainCube::complete_colors() {
    if (squares[1][0][2].sides_colors[4] == white && squares[1][0][2].sides_colors[red] == red) {
        check_white_cross[red] = true;
    } else {
        check_white_cross[red] = false;
    }
    if (squares[2][0][1].sides_colors[4] == white && squares[2][0][1].sides_colors[green] == green) {
        check_white_cross[green] = true;
    } else {
        check_white_cross[green] = false;
    }
    if (squares[0][0][1].sides_colors[4] == white && squares[0][0][1].sides_colors[blue] == blue) {
        check_white_cross[blue] = true;
    } else {
        check_white_cross[blue] = false;
    }
    if (squares[1][0][0].sides_colors[4] == white && squares[1][0][0].sides_colors[orange] == orange) {
        check_white_cross[orange] = true;
    } else {
        check_white_cross[orange] = false;
    }
}

void MainCube::pifpaf_for_set_up_yellow_cornerns() {
    turnVertical(leftVert, down, 2);
    turnHorizontal(lowHor, right, 2);
    turnVertical(leftVert, up, 2);
    turnHorizontal(lowHor, left, 2);
}

void MainCube::pifpaf_red_white_green() {
    turnVertical(rightVert, up, 2);
    turnHorizontal(upHor, left, 2);
    turnVertical(rightVert, down, 2);
    turnHorizontal(upHor, right, 2);
}

void MainCube::pifpaf_red_white_blue() {
    turnAround(nearAround, round_right,2);
    turnHorizontal(upHor, left, 2);
    turnAround(nearAround, round_left,2);
    turnHorizontal(upHor, right, 2);
}

void MainCube::pifpaf_orange_white_green() {
    turnAround(farAround, round_left,2);
    turnHorizontal(upHor, left, 2);
    turnAround(farAround, round_right,2);
    turnHorizontal(upHor, right, 2);
}

void MainCube::pifpaf_orange_white_blue() {
    turnVertical(leftVert, down,2);
    turnHorizontal(upHor, left, 2);
    turnVertical(leftVert, up,2);
    turnHorizontal(upHor, right, 2);
}

bool MainCube::check_corners() {
    for (int i = 0; i < 4; i++) {
        if (!check_white_corners[i]) {
            return false;
        }
    }
    return true;
}

void MainCube::comb_red_green() {
    turnHorizontal(upHor, left, 2);
    turnVertical(rightVert, up, 2);
    turnHorizontal(upHor, right, 2);
    turnVertical(rightVert, down, 2);
    turnHorizontal(upHor, right, 2);
    turnAround(nearAround, round_left, 2);
    turnHorizontal(upHor, left, 2);
    turnAround(nearAround, round_right, 2);
}

void MainCube::comb_green_red() {
    turnHorizontal(upHor, right, 2);
    turnAround(nearAround, round_left, 2);
    turnHorizontal(upHor, left, 2);
    turnAround(nearAround, round_right, 2);
    turnHorizontal(upHor, left, 2);
    turnVertical(rightVert, up, 2);
    turnHorizontal(upHor, right, 2);
    turnVertical(rightVert, down, 2);
}

void MainCube::comb_red_blue() {
    turnHorizontal(upHor, right, 2);
    turnVertical(leftVert, up, 2);
    turnHorizontal(upHor, left, 2);
    turnVertical(leftVert, down, 2);
    turnHorizontal(upHor, left, 2);
    turnAround(nearAround, round_right, 2);
    turnHorizontal(upHor, right, 2);
    turnAround(nearAround, round_left, 2);
}

void MainCube::comb_blue_red() { // change
    turnHorizontal(upHor, left, 2);
    turnAround(nearAround, round_right, 2);
    turnHorizontal(upHor, right, 2);
    turnAround(nearAround, round_left, 2);
    turnHorizontal(upHor, right, 2);
    turnVertical(leftVert, up, 2);
    turnHorizontal(upHor, left, 2);
    turnVertical(leftVert, down, 2);
}

void MainCube::comb_orange_blue() {
    turnHorizontal(upHor, left, 2);
    turnVertical(leftVert, down, 2);
    turnHorizontal(upHor, right, 2);
    turnVertical(leftVert, up, 2);
    turnHorizontal(upHor, right, 2);
    turnAround(farAround, round_right, 2);
    turnHorizontal(upHor, left, 2);
    turnAround(farAround, round_left, 2);
}

void MainCube::comb_blue_orange() { // change
    turnHorizontal(upHor, right, 2);
    turnAround(farAround, round_right, 2);
    turnHorizontal(upHor, left, 2);
    turnAround(farAround, round_left, 2);
    turnHorizontal(upHor, left, 2);
    turnVertical(leftVert, down, 2);
    turnHorizontal(upHor, right, 2);
    turnVertical(leftVert, up, 2);
}

void MainCube::comb_orange_green() {
    turnHorizontal(upHor, right, 2);
    turnVertical(rightVert, down, 2);
    turnHorizontal(upHor, left, 2);
    turnVertical(rightVert, up, 2);
    turnHorizontal(upHor, left, 2);
    turnAround(farAround, round_left, 2);
    turnHorizontal(upHor, right, 2);
    turnAround(farAround, round_right, 2);
}

void MainCube::comb_green_orange() {
    turnHorizontal(upHor, left, 2);
    turnAround(farAround, round_left, 2);
    turnHorizontal(upHor, right, 2);
    turnAround(farAround, round_right, 2);
    turnHorizontal(upHor, right, 2);
    turnVertical(rightVert, down, 2);
    turnHorizontal(upHor, left, 2);
    turnVertical(rightVert, up, 2);
}

void MainCube::make_right_positions_before_last_step() {
    while (!((squares[0][2][1].sides_colors[blue] == blue && squares[1][2][2].sides_colors[red] == red) ||
             (squares[0][2][1].sides_colors[blue] == blue && squares[1][2][0].sides_colors[orange] == orange) ||
             (squares[1][2][2].sides_colors[red] == red && squares[2][2][1].sides_colors[green] == green) ||
             (squares[1][2][0].sides_colors[orange] == orange && squares[2][2][1].sides_colors[green] == green))) {
        turnHorizontal(upHor, left, 2);
    }
}


void MainCube::turn_red_side() {
    turnVertical(rightVert, up,2);
    turnHorizontal(upHor, left, 2);
    turnVertical(rightVert, down,2);
    turnHorizontal(upHor, left, 2);
    turnVertical(rightVert, up,2);
    turnHorizontal(upHor, left, 2);
    turnHorizontal(upHor, left, 2);
    turnVertical(rightVert, down,2);
}

void MainCube::turn_green_side() {
    turnAround(farAround, round_left,2);
    turnHorizontal(upHor, left, 2);
    turnAround(farAround, round_right,2);
    turnHorizontal(upHor, left, 2);
    turnAround(farAround, round_left,2);
    turnHorizontal(upHor, left, 2);
    turnHorizontal(upHor, left, 2);
    turnAround(farAround, round_right,2);
}

void MainCube::turn_orange_side() {
    turnVertical(leftVert, down,2);
    turnHorizontal(upHor, left, 2);
    turnVertical(leftVert, up,2);
    turnHorizontal(upHor, left, 2);
    turnVertical(leftVert, down,2);
    turnHorizontal(upHor, left, 2);
    turnHorizontal(upHor, left, 2);
    turnVertical(leftVert, up,2);
}

void MainCube::turn_blue_side() {
    turnAround(nearAround, round_right,2);
    turnHorizontal(upHor, left, 2);
    turnAround(nearAround, round_left,2);
    turnHorizontal(upHor, left, 2);
    turnAround(nearAround, round_right,2);
    turnHorizontal(upHor, left, 2);
    turnHorizontal(upHor, left, 2);
    turnAround(nearAround, round_left,2);
}

void MainCube::change_positions_of_up_layer_for_yellow_centers() {
    turnAround(nearAround, round_right, 2);
    pifpaf_red_white_green();
    turnAround(nearAround, round_left, 2);
}

void MainCube::put_corners_if_orange_green() {
    turnAround(nearAround, round_right, 2);
    turnVertical(rightVert, up, 2);
    turnAround(nearAround, round_left, 2);
    turnVertical(leftVert, down, 2);
    turnAround(nearAround, round_right, 2);
    turnVertical(rightVert, down, 2);
    turnAround(nearAround, round_left, 2);
    turnVertical(leftVert, up, 2);
}

void MainCube::put_corners_if_orange_blue() {
    turnVertical(rightVert, up, 2);
    turnAround(farAround, round_left, 2);
    turnVertical(rightVert, down, 2);
    turnAround(nearAround, round_right, 2);

    turnVertical(rightVert, up, 2);
    turnAround(farAround, round_right, 2);
    turnVertical(rightVert, down, 2);
    turnAround(nearAround, round_left, 2);
}

void MainCube::put_corners_if_red_green() {
    turnVertical(leftVert, down, 2);
    turnAround(nearAround, round_right, 2);
    turnVertical(leftVert, up, 2);
    turnAround(farAround, round_left, 2);

    turnVertical(leftVert, down, 2);
    turnAround(nearAround, round_left, 2);
    turnVertical(leftVert, up, 2);
    turnAround(farAround, round_right, 2);
}

void MainCube::put_corners_if_red_blue() {
    turnAround(farAround, round_left, 2);
    turnVertical(leftVert, down, 2);
    turnAround(farAround, round_right, 2);
    turnVertical(rightVert, up, 2);
    turnAround(farAround, round_left, 2);
    turnVertical(leftVert, up, 2);
    turnAround(farAround, round_right, 2);
    turnVertical(rightVert, down, 2);
}