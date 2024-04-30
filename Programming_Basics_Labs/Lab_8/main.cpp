#include "MainCube.h"

int main() {

    MainCube mainScreen; // создаем экран, где будет находиться куб
    mainScreen.init(); // иницилизируем куб
    MainCube::changePositions(mainScreen); // меняем расположение кубика с помощью клавиш

}