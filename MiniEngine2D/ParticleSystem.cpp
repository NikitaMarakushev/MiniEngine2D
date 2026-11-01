#include "ParticleSystem.h"
#include <cmath>
#include <cstdlib>

ParticleSystem::ParticleSystem(int maxParticles) : maxParticles(maxParticles) {
    particles.reserve(maxParticles);
}

void ParticleSystem::Emit(float x, float y, int count, float speed, float lifetime, float size) {
    for (int i = 0; i < count; i++) {
        if (particles.size() >= maxParticles) break;

        Particle p;
        p.x = x;
        p.y = y;

        float angle = (rand() / (float)RAND_MAX) * 2.0f * 3.14159265358979323846f;
        float velocity = (rand() / (float)RAND_MAX) * speed;
        p.vx = std::cos(angle) * velocity;
        p.vy = std::sin(angle) * velocity;

        p.lifetime = lifetime;
        p.maxLifetime = lifetime;
        p.size = size;

        p.r = 1.0f;
        p.g = 1.0f;
        p.b = 1.0f;
        p.a = 1.0f;

        particles.push_back(p);
    }
}

void ParticleSystem::Update(float dt) {
    for (int i = particles.size() - 1; i >= 0; i--) {
        Particle& p = particles[i];

        p.x += p.vx * dt;
        p.y += p.vy * dt;

        p.lifetime -= dt;

        p.a = p.lifetime / p.maxLifetime;

        if (p.lifetime <= 0.0f) {
            particles[i] = particles.back();
            particles.pop_back();
        }
    }
}