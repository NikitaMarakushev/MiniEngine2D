#include "Sprite.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Sprite::Sprite(Texture* tex, float x, float y, float w, float h)
    : texture(tex), x(x), y(y), width(w), height(h), rotation(0) {

    float vertices[] = {
        0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
       -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
       -0.5f,  0.5f, 0.0f,  0.0f, 1.0f
    };

    unsigned int indices[] = { 0, 1, 3, 1, 2, 3 };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Sprite::draw(Shader& shader, Camera& camera, int screenWidth, int screenHeight) {
    float ndcX = (x / screenWidth) * 2.0f - 1.0f;
    float ndcY = 1.0f - (y / screenHeight) * 2.0f;
    float ndcW = (width / screenWidth) * 2.0f;
    float ndcH = (height / screenHeight) * 2.0f;

    float rad = rotation * 3.14159265358979323846f / 180.0f;
    float cosR = std::cos(rad);
    float sinR = std::sin(rad);

    float model[16] = {
        ndcW * cosR,  ndcW * sinR,  0.0f, 0.0f,
       -ndcH * sinR,  ndcH * cosR,  0.0f, 0.0f,
        0.0f,         0.0f,         1.0f, 0.0f,
        ndcX,         ndcY,         0.0f, 1.0f
    };

    shader.setMat4("model", model);
    shader.setMat4("view", camera.getViewMatrix());

    texture->bind(0);
    shader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Sprite::~Sprite() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}