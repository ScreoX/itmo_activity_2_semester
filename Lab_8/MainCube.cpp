#include "MainCube.h"

void MainCube::Draw(std::vector<Colors*> shaders, glm::mat4 MVP) { //рисуем каждый кубик
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                squares[x][y][z].Draw(shaders, MVP);
            }
        }
    }
}

void MainCube::Init() { //устанавливаем центры кубиков относительно нашего
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                squares[x][y][z].SetX(float(x - 1)*(size/3));
                squares[x][y][z].SetY(float(y - 1)*(size/3));
                squares[x][y][z].SetZ(float(z - 1)*(size/3));
                squares[x][y][z].Init(size); //инициализируем их
            }
        }
    }
}

void MainCube::turnVertical(int vertical, int mode) { //свапаем кубики соответствующие после их поворотов вокруг оси
    for (int y = 0; y < 3; y++) {
        for (int z = 0; z < 3; z++) {
            if (mode == down) {
                squares[vertical][y][z].turndown();
            }
            else if (mode == up) {
                squares[vertical][y][z].turnup();
            }
        }
    }
    if (mode == down) {
        for (int i = 0; i < 6; i++) {
            squares[vertical][2][0].sides_colors[i] = squares[vertical][0][0].sides_colors[i];
            squares[vertical][2][2].sides_colors[i] = squares[vertical][2][0].sides_colors[i];
            squares[vertical][0][0].sides_colors[i] = squares[vertical][0][2].sides_colors[i];
            squares[vertical][0][2].sides_colors[i] = squares[vertical][2][2].sides_colors[i];
        }
    }
    else if (mode == up){
        for (int i = 0; i < 6; i++) {
            squares[vertical][2][0].sides_colors[i] = squares[vertical][2][2].sides_colors[i];
            squares[vertical][0][2].sides_colors[i] = squares[vertical][0][0].sides_colors[i];
            squares[vertical][2][2].sides_colors[i] = squares[vertical][0][2].sides_colors[i];
            squares[vertical][0][0].sides_colors[i] = squares[vertical][2][0].sides_colors[i];
        }
    }
    if (mode == down) {
        for (int i = 0; i < 6; i++) {
            squares[vertical][1][0].sides_colors[i] = squares[vertical][0][1].sides_colors[i];
            squares[vertical][0][1].sides_colors[i] = squares[vertical][1][2].sides_colors[i];
            squares[vertical][1][2].sides_colors[i] = squares[vertical][2][1].sides_colors[i];
            squares[vertical][2][1].sides_colors[i] = squares[vertical][1][0].sides_colors[i];
        }
    }
    else if (mode == up){
        for (int i = 0; i < 6; i++) {
            squares[vertical][1][0].sides_colors[i] = squares[vertical][2][1].sides_colors[i];
            squares[vertical][0][1].sides_colors[i] = squares[vertical][1][0].sides_colors[i];
            squares[vertical][1][2].sides_colors[i] = squares[vertical][0][1].sides_colors[i];
            squares[vertical][2][1].sides_colors[i] = squares[vertical][1][2].sides_colors[i];
        }
    }
}

void MainCube::turnHorizontal(int layer, int mode) {
    for (int x = 0; x < 3; x++) {
        for (int z = 0; z < 3; z++) {
            if (mode == -1) {
                squares[x][layer][z].turnleft();
            }
            else {
                squares[x][layer][z].turnright();
            }
        }
    }
    if (mode == -1) {
        for (int i = 0; i < 6; i++) {
            squares[0][layer][2].sides_colors[i] = squares[0][layer][0].sides_colors[i];
            squares[2][layer][2].sides_colors[i] = squares[0][layer][2].sides_colors[i];
            squares[2][layer][0].sides_colors[i] = squares[2][layer][2].sides_colors[i];
            squares[0][layer][0].sides_colors[i] = squares[2][layer][0].sides_colors[i];
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            squares[2][layer][0].sides_colors[i] = squares[0][layer][0].sides_colors[i];
            squares[2][layer][2].sides_colors[i] = squares[2][layer][0].sides_colors[i];
            squares[0][layer][0].sides_colors[i] = squares[0][layer][2].sides_colors[i];
            squares[0][layer][2].sides_colors[i] = squares[2][layer][2].sides_colors[i];
        }
    }

    if (mode == -1) {
        for (int i = 0; i < 6; i++) {
            squares[0][layer][1].sides_colors[i] = squares[1][layer][0].sides_colors[i];
            squares[1][layer][2].sides_colors[i] = squares[0][layer][1].sides_colors[i];
            squares[2][layer][1].sides_colors[i] = squares[1][layer][2].sides_colors[i];
            squares[1][layer][0].sides_colors[i] = squares[2][layer][1].sides_colors[i];
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            squares[2][layer][1].sides_colors[i] = squares[1][layer][0].sides_colors[i];
            squares[1][layer][0].sides_colors[i] = squares[0][layer][1].sides_colors[i];
            squares[0][layer][1].sides_colors[i] = squares[1][layer][2].sides_colors[i];
            squares[1][layer][2].sides_colors[i] = squares[2][layer][1].sides_colors[i];
        }
    }
}

void MainCube::turnAround(int side, int mode) {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            squares[x][y][side].turndown();
            if (mode == -1) {
                squares[x][y][side].turnright();
            }
            else {
                squares[x][y][side].turnleft();
            }
            squares[x][y][side].turnup();
        }
    }
    if (mode == -1) {
        for (int i = 0; i < 6; i++) {
            squares[2][0][side].sides_colors[i] = squares[0][0][side].sides_colors[i];
            squares[2][2][side].sides_colors[i] = squares[2][0][side].sides_colors[i];
            squares[0][2][side].sides_colors[i] = squares[2][2][side].sides_colors[i];
            squares[0][0][side].sides_colors[i] = squares[0][2][side].sides_colors[i];
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            squares[0][2][side].sides_colors[i] = squares[0][0][side].sides_colors[i];
            squares[2][2][side].sides_colors[i] = squares[0][2][side].sides_colors[i];
            squares[2][0][side].sides_colors[i] = squares[2][2][side].sides_colors[i];
            squares[0][0][side].sides_colors[i] = squares[2][0][side].sides_colors[i];
        }
    }

    if (mode == -1) {
        for (int i = 0; i < 6; i++) {
            squares[2][1][side].sides_colors[i] = squares[1][0][side].sides_colors[i];
            squares[1][2][side].sides_colors[i] = squares[2][1][side].sides_colors[i];
            squares[0][1][side].sides_colors[i] = squares[1][2][side].sides_colors[i];
            squares[1][0][side].sides_colors[i] = squares[0][1][side].sides_colors[i];
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            squares[1][2][side].sides_colors[i] = squares[0][1][side].sides_colors[i];
            squares[2][1][side].sides_colors[i] = squares[1][2][side].sides_colors[i];
            squares[1][0][side].sides_colors[i] = squares[2][1][side].sides_colors[i];
            squares[0][1][side].sides_colors[i] = squares[1][0][side].sides_colors[i];
        }
    }
}

void MainCube::shuffle() {
    int countOperations = rand() % 1000;
    FILE* save = fopen("../OutputAndInput/input.txt", "w");
    char way, id, mode;
    for (int i = 0; i < countOperations; i++) {
        way = rand()%3;
        id = rand()%3;
        mode = rand()%2-1;
        if (way == 0) {
            turnHorizontal(id, mode);
        }
        else if (way == 1){
            turnVertical(id, mode);
        }
        else {
            turnAround(id, mode);
        }
        glLoadIdentity();
        glFinish();
        std::putc(way+97,save);
        std::putc(id+97,save);
        std::putc(mode+98,save);
    }
    std::fclose(save);
}