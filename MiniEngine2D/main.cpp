#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Texture.h"
#include "Sprite.h"
#include "Camera.h"
#include <iostream>
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "MiniEngine2D - Camera", NULL, NULL);
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
    Texture tex("texture.png");

    const int WORLD_WIDTH = 2000;
    const int WORLD_HEIGHT = 2000;

    Sprite player(&tex, WORLD_WIDTH / 2, WORLD_HEIGHT / 2, 128, 128);

    Camera camera(WORLD_WIDTH / 2 - 400, WORLD_HEIGHT / 2 - 300);

    std::vector<Sprite*> objects;
    for (int i = 0; i < 50; i++) {
        float x = (float)(rand() % WORLD_WIDTH);
        float y = (float)(rand() % WORLD_HEIGHT);
        float size = 32.0f + (float)(rand() % 96);
        objects.push_back(new Sprite(&tex, x, y, size, size));
    }

    float lastTime = (float)glfwGetTime();
    float speed = 300.0f;

    while (!glfwWindowShouldClose(window)) {
        float currentTime = (float)glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            player.y -= speed * dt;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            player.y += speed * dt;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            player.x -= speed * dt;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            player.x += speed * dt;

        if (player.x < 0) player.x = 0;
        if (player.y < 0) player.y = 0;
        if (player.x > WORLD_WIDTH) player.x = WORLD_WIDTH;
        if (player.y > WORLD_HEIGHT) player.y = WORLD_HEIGHT;

        camera.follow(player.x, player.y, 800, 600);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (Sprite* obj : objects) {
            obj->draw(shader, camera, WORLD_WIDTH, WORLD_HEIGHT);
        }

        player.draw(shader, camera, WORLD_WIDTH, WORLD_HEIGHT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    for (Sprite* obj : objects) {
        delete obj;
    }

    glfwTerminate();
    return 0;
}