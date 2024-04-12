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
                }
                iteration = (iteration + 1) % 6;
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
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_M)) { // вроде работает
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_M)) {

                mainScreen.solve_with_algorithms();

                reverse(mainScreen.operations_show.begin(), mainScreen.operations_show.end()); // развернул, так как делал emplace_back
                while(!mainScreen.operations_show.empty()) {
                    mainScreen.show_operations_of_solving();
                    mainScreen.drawCube(cords_vis);
                }
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
        while (glfwGetTime() - startTime < 0.2) {}
    } else {
        while (glfwGetTime() - startTime < 0.5) {}
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
    double startTime = glfwGetTime();
    if (flag == 3) {
        while (glfwGetTime() - startTime < 0.2) {}
    } else {
        while (glfwGetTime() - startTime < 0.5) {}
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

    double startTime = glfwGetTime();
    if (flag == 3) {
        while (glfwGetTime() - startTime < 0.2) {}
    } else {
        while (glfwGetTime() - startTime < 0.5) {}
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
    int countOperations = 15;

    FILE* save = fopen("../OutputAndInput/input.txt", "w");
    char way, id, orientation;
    for (int i = 0; i < countOperations; i++) {
        way = rand()%3;
        id = rand()%3;
        if (way == 0) {
            orientation = rand() % 2 + 2;
            turnHorizontal(id, orientation, 3);
            drawCube(cordsVisual);
        }
        else if (way == 1){
            orientation = rand() % 2;
            turnVertical(id, orientation, 3);
            drawCube(cordsVisual);
        }
        else {
            orientation = rand() % 2 + 4;
            turnAround(id, orientation, 3);
            drawCube(cordsVisual);
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
    } else if (operation == left || operation == right) {
        turnHorizontal(index, operation, -1);
    } else if (operation == round_left || operation == round_right) {
        turnAround(index, operation, -1);
    }
}

void MainCube::solve_with_algorithms() {
    set_up_centers(); // устанавливаю для удобства центры

    while (!checkWhiteCross()) {
        complete_colors();
        white_cross();
        for (int i = 0; i < 4; i++) {
            // 0 - orange
            // 1 - blue
            // 2 - red
            // 3 - green
            if (!check_white_cross[i]) {
                if (i == 0) {
                    turnAround(farAround, round_right,2);
                } else if (i == 1) {
                    turnVertical(leftVert, up, 2);
                } else if (i == 2) {
                    turnAround(nearAround, left, 2);
                } else {
                    turnVertical(rightVert, down, 2);
                }
            }
        }
    }

    go_back();
}

void MainCube::show_operations_of_solving() {
    auto [index, operation] = operations_show.back();
    operations_show.pop_back();
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

void MainCube::white_cross() { // нужно учесть, что я не нарушаю уже стоящие центры при поворотах
    // для верхней части, где hor = 2, надо знать 5 индекс и индекс цетра этой грани
    int counter = 0;
    for (int vertical = 0; vertical < 3; vertical++) {
        for (int side = 0; side < 3; side++) {
            if ((vertical == 0 && side == 0) || (vertical == 2 && side == 2) || (vertical == 0 && side == 2) || (vertical == 2 && side == 0)) {
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
                        check_white_cross[center] = true;
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
                        } else { // orange
                            turnHorizontal(upHor, left, 2);
                            turnVertical(leftVert, up, 2);
                            turnAround(farAround, round_left, 2);

                            // вернуть прошлую сторону обратно
                            turnVertical(leftVert, down, 2);
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

                        } else { // green

                            turnHorizontal(upHor, right, 2);
                            turnAround(nearAround, round_right, 2);
                            turnVertical(rightVert, down, 2);

                            // вернуть прошлую сторону обратно
                            turnAround(nearAround, round_left, 2);

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

                        } else { // blue
                            turnHorizontal(upHor, left, 2);
                            turnAround(nearAround, round_left, 2);
                            turnVertical(leftVert, down, 2);

                            // вернуть прошлую сторону обратно
                            turnAround(nearAround, round_right, 2);

                        }
                    } else { // orange
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
                        } else { // red
                            turnHorizontal(upHor, left, 2);
                            turnVertical(rightVert, down, 2);
                            turnAround(nearAround, round_right, 2);

                            // вернуть прошлую сторону обратно
                            turnVertical(rightVert, up, 2);
                        }
                    }
                    check_white_cross[color_above_white] = true;
                }
            }
        }
    }
//    //теперь будем искать на втором уровне (hor = 1)
//    for (int vertical = 0; vertical < 3; vertical++) {
//        for (int side = 0; side < 3; side++) {
//            char center = find_center(vertical, side); // центр на текущей итерации
//            char color_near_center = squares[vertical][middleHor][side].sides_colors[center];
//
//        }
//    }
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

void MainCube::go_back() {

    std::reverse(operations_back.begin(), operations_back.end());

    for (auto [index, operation] : operations_back) {

        if (operation == up || operation == down) {
            turnVertical(index, operation, -1);
        } else if (operation == left || operation == right) {
            turnHorizontal(index, operation, -1);
        } else if (operation == round_left || operation == round_right) {
            turnAround(index, operation, -1);
        }
    }

//    operations_back.clear();
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
    }
    if (squares[2][0][1].sides_colors[4] == white && squares[2][0][1].sides_colors[green] == green) {
        check_white_cross[green] = true;
    }
    if (squares[0][0][1].sides_colors[4] == white && squares[0][0][1].sides_colors[blue] == blue) {
        check_white_cross[blue] = true;
    }
    if (squares[1][0][0].sides_colors[4] == white && squares[1][0][0].sides_colors[orange] == orange) {
        check_white_cross[orange] = true;
    }
}
