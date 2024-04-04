cmake_minimum_required(VERSION 3.27)
project(cube_rube)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
add_executable(${PROJECT_NAME}
        main.cpp
        Algorighms.cpp
        Algorighms.h
        Cube.cpp
        Cube.h
)

target_link_libraries(${PROJECT_NAME}
        glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES}
        libglew_static
        glm::glm
)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_INCLUDES})



