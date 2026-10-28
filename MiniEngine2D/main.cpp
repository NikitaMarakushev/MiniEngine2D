#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "TileMap.h"
#include "BatchRenderer.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "MiniEngine2D - Batch Rendering", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader shader("sprite.vert", "sprite.frag");
    Texture wallTex("texture.png");
    Texture floorTex("texture.png");
    Texture playerTex("player_sheet.png");

    TileMap level("level.txt", &wallTex, &floorTex, &playerTex);

    float playerX = (level.width * level.tileSize) / 2.0f;
    float playerY = (level.height * level.tileSize) / 2.0f;
    Camera camera(playerX - 400, playerY - 300, 800, 600);

    BatchRenderer batch(2000);

    float lastTime = (float)glfwGetTime();
    float speed = 200.0f;

    while (!glfwWindowShouldClose(window)) {
        float currentTime = (float)glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) playerY -= speed * dt;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) playerY += speed * dt;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) playerX -= speed * dt;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) playerX += speed * dt;

        camera.follow(playerX, playerY, 800, 600);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        batch.begin();

        for (int y = 0; y < level.height; y++) {
            for (int x = 0; x < level.width; x++) {
                int tileType = level.getTile(x, y);
                if (tileType == 0) continue;

                float px = x * level.tileSize + level.tileSize / 2.0f;
                float py = y * level.tileSize + level.tileSize / 2.0f;

                Texture* tex = nullptr;
                float r = 1.0f, g = 1.0f, b = 1.0f;

                switch (tileType) {
                case 1: tex = &wallTex; r = 0.5f; g = 0.5f; b = 0.5f; break;
                case 2: tex = &playerTex; r = 1.0f; g = 0.3f; b = 0.3f; break;
                case 3: tex = &playerTex; r = 0.3f; g = 0.3f; b = 1.0f; break;
                case 4: tex = &playerTex; r = 0.3f; g = 1.0f; b = 0.3f; break;
                }

                if (tex) {
                    batch.drawSprite(tex, px, py, level.tileSize, level.tileSize, 0.0f, r, g, b);
                }
            }
        }

        batch.drawSprite(&playerTex, playerX, playerY, 48, 48, 0.0f, 1.0f, 1.0f, 1.0f);

        batch.end(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}