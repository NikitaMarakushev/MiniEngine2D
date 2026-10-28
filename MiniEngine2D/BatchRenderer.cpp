#include "BatchRenderer.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

BatchRenderer::BatchRenderer(int maxSprites) : maxSprites(maxSprites), vertexCount(0) {
    vertices.reserve(maxSprites * 4);
    indices.reserve(maxSprites * 6);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, maxSprites * 4 * sizeof(VertexData), nullptr, GL_DYNAMIC_DRAW);

    for (int i = 0; i < maxSprites; i++) {
        unsigned int offset = i * 4;
        indices.push_back(offset + 0);
        indices.push_back(offset + 1);
        indices.push_back(offset + 3);
        indices.push_back(offset + 1);
        indices.push_back(offset + 2);
        indices.push_back(offset + 3);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void BatchRenderer::begin() {
    vertexCount = 0;
    vertices.clear();
}

void BatchRenderer::drawSprite(Texture* tex, float x, float y, float width, float height,
    float srcX, float srcY, float srcW, float srcH,
    float rotation, float r, float g, float b) {
    if (vertexCount >= maxSprites * 4) return;

    float rad = rotation * 3.14159265358979323846f / 180.0f;
    float cosR = std::cos(rad);
    float sinR = std::sin(rad);

    float texW = (float)tex->width;
    float texH = (float)tex->height;

    float u0 = srcX / texW;
    float v0 = srcY / texH;
    float u1 = (srcX + srcW) / texW;
    float v1 = (srcY + srcH) / texH;

    float hw = width / 2.0f;
    float hh = height / 2.0f;
\
    float corners[4][2] = {
        { -hw, -hh },{ hw, -hh },{ hw, hh },{ -hw, hh }
    };

    // UV для каждого угла
    float uvs[4][2] = {
        { u0, v0 },{ u1, v0 },{ u1, v1 },{ u0, v1 }
    };

    for (int i = 0; i < 4; i++) {
        float px = corners[i][0] * cosR - corners[i][1] * sinR + x;
        float py = corners[i][0] * sinR + corners[i][1] * cosR + y;

        VertexData v;
        v.x = px;
        v.y = py;
        v.z = 0.0f;
        v.u = uvs[i][0];
        v.v = uvs[i][1];
        v.r = r;
        v.g = g;
        v.b = b;

        vertices.push_back(v);
    }
    vertexCount += 4;
}

void BatchRenderer::end(Shader& shader, Camera& camera) {
    if (vertexCount == 0) return;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(VertexData), vertices.data());

    shader.use();
    shader.setMat4("view", camera.getViewMatrix());
    shader.setMat4("projection", camera.getProjectionMatrix());

    glDrawElements(GL_TRIANGLES, vertexCount / 4 * 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

BatchRenderer::~BatchRenderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}