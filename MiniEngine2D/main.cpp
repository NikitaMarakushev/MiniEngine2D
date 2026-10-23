#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Texture.h"
#include "Sprite.h"
#include "Camera.h"
#include "TileMap.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "MiniEngine2D - TileMap", NULL, NULL);
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
    Texture objTex("texture.png");

    TileMap level("level.txt", &wallTex, &floorTex, &objTex);

    float playerX = (level.width * level.tileSize) / 2.0f;
    float playerY = (level.height * level.tileSize) / 2.0f;
    Sprite player(&objTex, playerX, playerY, 48, 48);
    player.setColor(1.0f, 1.0f, 0.0f);

    Camera camera(playerX - 400, playerY - 300);

    float lastTime = (float)glfwGetTime();
    float speed = 200.0f;

    while (!glfwWindowShouldClose(window)) {
        float currentTime = (float)glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime;

        float oldX = player.x;
        float oldY = player.y;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            player.y -= speed * dt;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            player.y += speed * dt;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            player.x -= speed * dt;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            player.x += speed * dt;

        if (level.isWall(player.x, player.y, player.width, player.height)) {
            player.x = oldX;
            player.y = oldY;
        }

        camera.follow(player.x, player.y, 800, 600);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        level.draw(shader, camera, 800, 600);
        player.draw(shader, camera, 800, 600);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}