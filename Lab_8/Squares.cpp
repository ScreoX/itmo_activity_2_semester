#include "Squares.h"


void Squares::Init(float size) {
    const float a = 0.16f;

    CordsSquares new_cords = GetCords();
    
    all_sides.frontLeftBottom[0] = new_cords.x - (a * size);
    all_sides.frontLeftBottom[1] = new_cords.y - (a * size);
    all_sides.frontLeftBottom[2] = new_cords.z - (a * size);

    all_sides.frontRightBottom[0] = new_cords.x + (a * size);
    all_sides.frontRightBottom[1] = new_cords.y - (a * size);
    all_sides.frontRightBottom[2] = new_cords.z - (a * size);

    all_sides.frontRightUp[0] = new_cords.x + (a * size);
    all_sides.frontRightUp[1] = new_cords.y + (a * size);
    all_sides.frontRightUp[2] = new_cords.z - (a * size);

    all_sides.frontLeftUp[0] = new_cords.x - (a * size);
    all_sides.frontLeftUp[1] = new_cords.y + (a * size);
    all_sides.frontLeftUp[2] = new_cords.z - (a * size);

    all_sides.backLeftBottom[0] = new_cords.x - (a * size);
    all_sides.backLeftBottom[1] = new_cords.y - (a * size);
    all_sides.backLeftBottom[2] = new_cords.z + (a * size);

    all_sides.backRightBottom[0] = new_cords.x + (a * size);
    all_sides.backRightBottom[1] = new_cords.y - (a * size);
    all_sides.backRightBottom[2] = new_cords.z + (a * size);

    all_sides.backLeftUp[0] = new_cords.x - (a * size);
    all_sides.backLeftUp[1] = new_cords.y + (a * size);
    all_sides.backLeftUp[2] = new_cords.z + (a * size);

    all_sides.backRightUp[0] = new_cords.x + (a * size);
    all_sides.backRightUp[1] = new_cords.y + (a * size);
    all_sides.backRightUp[2] = new_cords.z + (a * size);

}

void Squares::Draw(std::vector<Colors *> shaders, glm::mat4 MVP) {
    std::vector<float> edges;

    // Front Side
    for (float i: all_sides.frontLeftUp) {
        edges.push_back(i);
    }

    for (float i: all_sides.frontLeftBottom) {
        edges.push_back(i);
    }
    for (float i: all_sides.frontRightBottom) {
        edges.push_back(i);
    }
    for (float i: all_sides.frontLeftUp) {
        edges.push_back(i);
    }
    for (float i: all_sides.frontRightBottom) {
        edges.push_back(i);
    }
    for (float i: all_sides.frontRightUp) {
        edges.push_back(i);
    }
    // Left Side
    for (float i: all_sides.frontLeftBottom) {
        edges.push_back(i);
    }
    for (float i: all_sides.backLeftUp) {
        edges.push_back(i);
    }
    for (float i: all_sides.backLeftBottom) {
        edges.push_back(i);
    }
    for (float i: all_sides.frontLeftBottom) {
        edges.push_back(i);
    }
    for (float i: all_sides.backLeftUp) {
        edges.push_back(i);
    }
    for (float i: all_sides.frontLeftUp) {
        edges.push_back(i);
    }
    // Back Side
    for (float i: all_sides.backLeftUp) {
        edges.push_back(i);
    }
    for (float i: all_sides.backLeftBottom) {
        edges.push_back(i);
    }
    for (float i: all_sides.backRightBottom) {
        edges.push_back(i);
    }
    for (float i: all_sides.backLeftUp) {
        edges.push_back(i);
    }
    for (float i: all_sides.backRightBottom) {
        edges.push_back(i);
    }
    for (float i: all_sides.backRightUp) {
        edges.push_back(i);
    }
    // Right Side
    for (float i: all_sides.frontRightBottom) {
        edges.push_back(i);
    }
    for (float i: all_sides.backRightUp) {
        edges.push_back(i);
    }
    for (float i: all_sides.backRightBottom) {
        edges.push_back(i);
    }
    for (float i: all_sides.frontRightBottom) {
        edges.push_back(i);
    }
    for (float i: all_sides.backRightUp) {
        edges.push_back(i);
    }
    for (float i: all_sides.frontRightUp) {
        edges.push_back(i);
    }
    // Bottom Side
    for (float i: all_sides.frontLeftBottom) {
        edges.push_back(i);
    }
    for (float i: all_sides.frontRightBottom) {
        edges.push_back(i);
    }
    for (float i: all_sides.backRightBottom) {
        edges.push_back(i);
    }
    for (float i: all_sides.frontLeftBottom) {
        edges.push_back(i);
    }
    for (float i: all_sides.backLeftBottom) {
        edges.push_back(i);
    }
    for (float i: all_sides.backRightBottom) {
        edges.push_back(i);
    }
    // Up Side
    for (float i: all_sides.frontLeftUp) {
        edges.push_back(i);
    }
    for (float i: all_sides.frontRightUp) {
        edges.push_back(i);
    }
    for (float i: all_sides.backLeftUp) {
        edges.push_back(i);
    }
    for (float i: all_sides.backRightUp) {
        edges.push_back(i);
    }
    for (float i: all_sides.frontRightUp) {
        edges.push_back(i);
    }
    for (float i: all_sides.backLeftUp) {
        edges.push_back(i);
    }

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    GLfloat g_vertex_buffer_data[edges.size()];
    for (int gran = 0; gran < edges.size(); gran++) {
        g_vertex_buffer_data[gran] = edges[gran];
    }
    edges.clear();
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);
    for (int i = 0; i < 6; i++) {
        GLuint MatrixID = glGetUniformLocation(shaders[sides_colors[i]]->id, "MVP");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        shaders[sides_colors[i]]->use();
        glDrawArrays(GL_TRIANGLES, i * 6, 6);
    }
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteBuffers(1, &vertexbuffer);
}

void Squares::turnright() {
    char newsides[6];

    newsides[1] = sides_colors[0];
    newsides[2] = sides_colors[1];
    newsides[3] = sides_colors[2];
    newsides[0] = sides_colors[3];
    newsides[4] = sides_colors[4];
    newsides[5] = sides_colors[5];

    for (int i = 0; i < 6; i++) {
        sides_colors[i] = newsides[i];
    }
}

void Squares::turnleft() {
    char newsides_colors[6];

    newsides_colors[0] = sides_colors[1];
    newsides_colors[1] = sides_colors[2];
    newsides_colors[2] = sides_colors[3];
    newsides_colors[3] = sides_colors[0];
    newsides_colors[4] = sides_colors[4];
    newsides_colors[5] = sides_colors[5];

    for (int i = 0; i < 6; i++) {
        sides_colors[i] = newsides_colors[i];
    }
}

void Squares::turnup() {
    char newsides_colors[6];

    newsides_colors[0] = sides_colors[5];
    newsides_colors[5] = sides_colors[2];
    newsides_colors[2] = sides_colors[4];
    newsides_colors[1] = sides_colors[1];
    newsides_colors[3] = sides_colors[3];
    newsides_colors[4] = sides_colors[0];

    for (int i = 0; i < 6; i++) {
        sides_colors[i] = newsides_colors[i];
    }
}

void Squares::turndown() {
    char newsides_colors[6];

    newsides_colors[0] = sides_colors[4];
    newsides_colors[1] = sides_colors[1];
    newsides_colors[2] = sides_colors[5];
    newsides_colors[3] = sides_colors[3];
    newsides_colors[4] = sides_colors[2];
    newsides_colors[5] = sides_colors[0];

    for (int i = 0; i < 6; i++) {
        sides_colors[i] = newsides_colors[i];
    }
}

void Squares::FindSide(int index, char color) {
    sides_colors[index] = color;
}

CordsSquares Squares::GetCords() const {
    return cords;
}

void Squares::ChangeCords(float x, float y, float z) {
    cords = {x, y, z};
}

