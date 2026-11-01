#pragma once
#include <vector>

struct Particle {
    float x, y;
    float vx, vy;
    float lifetime;
    float maxLifetime;
    float size;
    float r, g, b, a;
};

class ParticleSystem {
public:
    ParticleSystem(int maxParticles = 1000);

    void Emit(float x, float y, int count, float speed, float lifetime, float size);
    void Update(float dt);

    const std::vector<Particle>& GetParticles() const { return particles; }

private:
    std::vector<Particle> particles;
    int maxParticles;
};