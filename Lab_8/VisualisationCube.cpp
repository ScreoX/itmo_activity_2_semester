#include "VisualisationCube.h"


using namespace glm;

int CubeDlg::init() {

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

    MyCube.Init();

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

void CubeDlg::drawCube(Cords cords) {
    glLoadIdentity();
    glFinish();
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // задний фон
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glm::mat4 Projection = glm::perspective(glm::radians(GLfloat(90)), 1.0f, 0.1f, 100.0f);
    glm::mat4 Camera = glm::lookAt( glm::vec3(cords.x, cords.y, cords.z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // изначальное расположение камеры кубика
    auto Model = glm::mat4(1.0f);
    glm::mat4 MVP = Projection * Camera * Model;

    MyCube.Draw(colors, MVP);
    glfwSwapBuffers(screen);
}

void CubeDlg::changePositions(CubeDlg& mainScreen) {
    Cords cords = Cords(1,1,1);
    int iteration = 0;
    bool wasReleased = false;
    do {
        // Change Positions
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_ENTER) == GLFW_PRESS) {
            if (!wasReleased) {
                switch(iteration) {
                    case 0: cords.x = 1, cords.y = 1, cords.z = 1; break;
                    case 1: cords.x = 1, cords.y = 1, cords.z = -1; break;
                    case 2: cords.x = -1, cords.y = 1, cords.z = -1; break;
                    case 3: cords.x = -1, cords.y = 1, cords.z = 1; break;
                    case 4: cords.x = 1, cords.y = -1, cords.z = 1; break;
                    case 5: cords.x = 1, cords.y = -1, cords.z = -1; break;
                    case 6: cords.x = -1, cords.y = -1, cords.z = -1; break;
                    case 7: cords.x = -1, cords.y = -1, cords.z = 1; break;
                }
                iteration = (iteration + 1) % 8;
                wasReleased = true;
            }
        } else {
            wasReleased = false;
        }

        // Shuffle
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_TAB)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_TAB)) {
                mainScreen.MyCube.shuffle();
            }
        }


        // Turning MainCube

        // [vertical][horizontal][round] - indexes

        // Vertical
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_A)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_A)) {
                mainScreen.MyCube.turnVertical(high_or_left,down); // correct
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_S)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_S)) {
                mainScreen.MyCube.turnVertical(middle_or_central,down);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_D)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_D)) {
                mainScreen.MyCube.turnVertical(low_or_right,down);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_Q)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_Q)) {
                mainScreen.MyCube.turnVertical(high_or_left,up);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_W)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_W)) {
                mainScreen.MyCube.turnVertical(middle_or_central,up);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_E)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_E)) {
                mainScreen.MyCube.turnVertical(low_or_right,up);
            }
        }

        // Horizontal
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_R)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_R)) {
                mainScreen.MyCube.turnHorizontal(high_or_left,-1); // ошибка тут
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_T)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_T)) {
                mainScreen.MyCube.turnHorizontal(middle_or_central,-1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_Y)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_Y)) {
                mainScreen.MyCube.turnHorizontal(low_or_right,-1); // ошибка тут
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_F)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_F)) {
                mainScreen.MyCube.turnHorizontal(0,1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_G)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_G)) {
                mainScreen.MyCube.turnHorizontal(1,1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_H)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_H)) {
                mainScreen.MyCube.turnHorizontal(2,1);
            }
        }

        // Around
        
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_U)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_U)) {
                mainScreen.MyCube.turnAround(2,-1);
            }
        }
        if (glfwGetKey(mainScreen.screen, GLFW_KEY_J)) {
            if (!glfwGetKey(mainScreen.screen, GLFW_KEY_J)) {
                mainScreen.MyCube.turnAround(2,1);
            }
        }
        mainScreen.drawCube(cords);
        glfwPollEvents();
    }

    while(glfwGetKey(mainScreen.screen, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(mainScreen.screen) == 0);
    glfwTerminate();
}

