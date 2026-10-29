#pragma once

struct Animation {
    int frameWidth;
    int frameHeight;
    int columns;
    int totalFrames;
    int currentFrame;
    float timer;
    float speed;

    Animation(int w, int h, int cols, int frames, float spd)
        : frameWidth(w), frameHeight(h), columns(cols),
        totalFrames(frames), currentFrame(0), timer(0.0f), speed(spd) {}

    void Update(float dt) {
        timer += dt;
        if (timer >= speed) {
            timer = 0.0f;
            currentFrame = (currentFrame + 1) % totalFrames;
        }
    }

    void GetSourceRect(int& x, int& y, int& w, int& h) {
        x = (currentFrame % columns) * frameWidth;
        y = (currentFrame / columns) * frameHeight;
        w = frameWidth;
        h = frameHeight;
    }
};