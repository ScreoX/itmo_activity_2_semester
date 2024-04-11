#include "VisualisationCube.h"

int main() {

    CubeDlg mainScreen; // создаем экран, где будет находиться куб
    mainScreen.init(); // иницилизируем куб
    CubeDlg::changePositions(mainScreen); // меняем расположение кубика с помощью клавиш

}