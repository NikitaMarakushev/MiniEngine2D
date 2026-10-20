#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Texture.h"
#include "Sprite.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "MiniEngine2D - Movement", NULL, NULL);
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

    Sprite player(&tex, 400, 300, 128, 128);
    Sprite enemy(&tex, 200, 200, 64, 64);

    float lastTime = (float)glfwGetTime();
    float speed = 300.0f;
    float rotSpeed = 180.0f;

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

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            player.rotation -= rotSpeed * dt;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            player.rotation += rotSpeed * dt;

        if (player.x < 0) player.x = 0;
        if (player.y < 0) player.y = 0;
        if (player.x > 800) player.x = 800;
        if (player.y > 600) player.y = 600;

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        player.draw(shader, 800, 600);
        enemy.draw(shader, 800, 600);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}