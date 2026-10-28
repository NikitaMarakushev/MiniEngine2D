#pragma once
#include <glad/glad.h>
#include "Shader.h"
#include "Texture.h"
#include <vector>

struct VertexData {
    float x, y, z;
    float u, v;
    float r, g, b;
};

class BatchRenderer {
public:
    BatchRenderer(int maxSprites = 1000);
    ~BatchRenderer();

    void begin();
    void drawSprite(Texture* tex, float x, float y, float width, float height,
        float rotation = 0.0f, float r = 1.0f, float g = 1.0f, float b = 1.0f);
    void end(Shader& shader);

private:
    int maxSprites;
    int vertexCount;
    std::vector<VertexData> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;
};