#include "Squares.h"

void Squares::Draw(std::vector<Colors *> shaders, glm::mat4 MVP) {
    std::vector<float> edges;
    //front

    for (float i: faceLeftUp) {
        edges.push_back(i);
    }

    for (float i: faceLeftBottom) {
        edges.push_back(i);
    }
    for (float i: faceRightBottom) {
        edges.push_back(i);
    }
    for (float i: faceLeftUp) {
        edges.push_back(i);
    }
    for (float i: faceRightBottom) {
        edges.push_back(i);
    }
    for (float i: faceRightUp) {
        edges.push_back(i);
    }
    //left
    for (float i: faceLeftBottom) {
        edges.push_back(i);
    }
    for (float i: backLeftUp) {
        edges.push_back(i);
    }
    for (float i: backLeftBottom) {
        edges.push_back(i);
    }
    for (float i: faceLeftBottom) {
        edges.push_back(i);
    }
    for (float i: backLeftUp) {
        edges.push_back(i);
    }
    for (float i: faceLeftUp) {
        edges.push_back(i);
    }
    //back
    for (float i: backLeftUp) {
        edges.push_back(i);
    }
    for (float i: backLeftBottom) {
        edges.push_back(i);
    }
    for (float i: backRightBottom) {
        edges.push_back(i);
    }
    for (float i: backLeftUp) {
        edges.push_back(i);
    }
    for (float i: backRightBottom) {
        edges.push_back(i);
    }
    for (float i: backRightUp) {
        edges.push_back(i);
    }
    //right
    for (float i: faceRightBottom) {
        edges.push_back(i);
    }
    for (float i: backRightUp) {
        edges.push_back(i);
    }
    for (float i: backRightBottom) {
        edges.push_back(i);
    }
    for (float i: faceRightBottom) {
        edges.push_back(i);
    }
    for (float i: backRightUp) {
        edges.push_back(i);
    }
    for (float i: faceRightUp) {
        edges.push_back(i);
    }
    //bottom
    for (float i: faceLeftBottom) {
        edges.push_back(i);
    }
    for (float i: faceRightBottom) {
        edges.push_back(i);
    }
    for (float i: backRightBottom) {
        edges.push_back(i);
    }
    for (float i: faceLeftBottom) {
        edges.push_back(i);
    }
    for (float i: backLeftBottom) {
        edges.push_back(i);
    }
    for (float i: backRightBottom) {
        edges.push_back(i);
    }
    //up
    for (float i: faceLeftUp) {
        edges.push_back(i);
    }
    for (float i: faceRightUp) {
        edges.push_back(i);
    }
    for (float i: backLeftUp) {
        edges.push_back(i);
    }
    for (float i: backRightUp) {
        edges.push_back(i);
    }
    for (float i: faceRightUp) {
        edges.push_back(i);
    }
    for (float i: backLeftUp) {
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    for (int i = 0; i < 6; i++) {
        GLuint MatrixID = glGetUniformLocation(shaders[sides_colors[i]]->id, "MVP");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        shaders[sides_colors[i]]->use();
        glDrawArrays(GL_TRIANGLES, i * 6, 6);
    }
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteBuffers(1, &vertexbuffer);
}

void Squares::Init(float size) {
    const float a = 0.16f;
    faceLeftBottom[0] = GetX() - (a * size);
    faceLeftBottom[1] = GetY() - (a * size);
    faceLeftBottom[2] = GetZ() - (a * size);

    faceRightBottom[0] = GetX() + (a * size);
    faceRightBottom[1] = GetY() - (a * size);
    faceRightBottom[2] = GetZ() - (a * size);

    faceRightUp[0] = GetX() + (a * size);
    faceRightUp[1] = GetY() + (a * size);
    faceRightUp[2] = GetZ() - (a * size);

    faceLeftUp[0] = GetX() - (a * size);
    faceLeftUp[1] = GetY() + (a * size);
    faceLeftUp[2] = GetZ() - (a * size);

    backLeftBottom[0] = GetX() - (a * size);
    backLeftBottom[1] = GetY() - (a * size);
    backLeftBottom[2] = GetZ() + (a * size);

    backRightBottom[0] = GetX() + (a * size);
    backRightBottom[1] = GetY() - (a * size);
    backRightBottom[2] = GetZ() + (a * size);

    backLeftUp[0] = GetX() - (a * size);
    backLeftUp[1] = GetY() + (a * size);
    backLeftUp[2] = GetZ() + (a * size);

    backRightUp[0] = GetX() + (a * size);
    backRightUp[1] = GetY() + (a * size);
    backRightUp[2] = GetZ() + (a * size);

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

float Squares::GetX() const {
    return X;
}

float Squares::GetY() const {
    return Y;
}

float Squares::GetZ() const {
    return Z;
}

void Squares::SetX(float x) {
    X = x;
}

void Squares::SetY(float y) {
    Y = y;
}

void Squares::SetZ(float z) {
    Z = z;
}

char Squares::Side(int id) {
    return sides_colors[id];
}

void Squares::FindSide(int index, int id) {
    sides_colors[index] = id;
}