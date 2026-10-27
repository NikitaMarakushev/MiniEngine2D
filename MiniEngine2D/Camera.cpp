#include "Camera.h"

Camera::Camera(float x, float y, int screenWidth, int screenHeight) : x(x), y(y) {
    updateProjectionMatrix(screenWidth, screenHeight);
    updateViewMatrix(screenWidth, screenHeight);
}

void Camera::follow(float targetX, float targetY, int screenWidth, int screenHeight) {
    x = targetX - screenWidth / 2.0f;
    y = targetY - screenHeight / 2.0f;
    updateViewMatrix(screenWidth, screenHeight);
}

float* Camera::getViewMatrix() {
    return viewMatrix;
}

float* Camera::getProjectionMatrix() {
    return projectionMatrix;
}

void Camera::updateViewMatrix(int screenWidth, int screenHeight) {
    viewMatrix[0] = 1.0f;  viewMatrix[4] = 0.0f;  viewMatrix[8] = 0.0f;  viewMatrix[12] = -x;
    viewMatrix[1] = 0.0f;  viewMatrix[5] = 1.0f;  viewMatrix[9] = 0.0f;  viewMatrix[13] = -y;
    viewMatrix[2] = 0.0f;  viewMatrix[6] = 0.0f;  viewMatrix[10] = 1.0f;  viewMatrix[14] = 0.0f;
    viewMatrix[3] = 0.0f;  viewMatrix[7] = 0.0f;  viewMatrix[11] = 0.0f;  viewMatrix[15] = 1.0f;
}

void Camera::updateProjectionMatrix(int screenWidth, int screenHeight) {
    float left = 0.0f;
    float right = (float)screenWidth;
    float bottom = (float)screenHeight;
    float top = 0.0f;
    float near = -1.0f;
    float far = 1.0f;

    projectionMatrix[0] = 2.0f / (right - left);
    projectionMatrix[1] = 0.0f;
    projectionMatrix[2] = 0.0f;
    projectionMatrix[3] = 0.0f;

    projectionMatrix[4] = 0.0f;
    projectionMatrix[5] = 2.0f / (top - bottom);
    projectionMatrix[6] = 0.0f;
    projectionMatrix[7] = 0.0f;

    projectionMatrix[8] = 0.0f;
    projectionMatrix[9] = 0.0f;
    projectionMatrix[10] = -2.0f / (far - near);
    projectionMatrix[11] = 0.0f;

    projectionMatrix[12] = -(right + left) / (right - left);
    projectionMatrix[13] = -(top + bottom) / (top - bottom);
    projectionMatrix[14] = -(far + near) / (far - near);
    projectionMatrix[15] = 1.0f;
}