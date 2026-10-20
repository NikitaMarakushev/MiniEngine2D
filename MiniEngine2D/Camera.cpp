#include "Camera.h"

Camera::Camera(float x, float y) : x(x), y(y) {
    updateViewMatrix(800, 600);
}

void Camera::follow(float targetX, float targetY, int screenWidth, int screenHeight) {
    x = targetX - screenWidth / 2.0f;
    y = targetY - screenHeight / 2.0f;
    updateViewMatrix(screenWidth, screenHeight);
}

float* Camera::getViewMatrix() {
    return viewMatrix;
}

void Camera::updateViewMatrix(int screenWidth, int screenHeight) {
    float ndcX = (x / screenWidth) * 2.0f - 1.0f;
    float ndcY = 1.0f - (y / screenHeight) * 2.0f;

    viewMatrix[0] = 1.0f;  viewMatrix[4] = 0.0f;  viewMatrix[8] = 0.0f;  viewMatrix[12] = -ndcX;
    viewMatrix[1] = 0.0f;  viewMatrix[5] = 1.0f;  viewMatrix[9] = 0.0f;  viewMatrix[13] = -ndcY;
    viewMatrix[2] = 0.0f;  viewMatrix[6] = 0.0f;  viewMatrix[10] = 1.0f;  viewMatrix[14] = 0.0f;
    viewMatrix[3] = 0.0f;  viewMatrix[7] = 0.0f;  viewMatrix[11] = 0.0f;  viewMatrix[15] = 1.0f;
}