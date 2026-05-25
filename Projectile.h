#pragma once
#include "GameObject.h"

class Projectile : public GameObject {

private:
    float speed;
    float lifetime;
    float maxLifetime;

    SDL_Texture* CreateTexture(SDL_Renderer* renderer);

public:

    void Render(SDL_Renderer* renderer) override;
    void Update(float dt) override;

    // bool IsDead() { return lifetime >= maxLifetime; }

    Projectile(SDL_Renderer* renderer, Vector2 startPos, float startRotation) : GameObject(renderer) {

        tag = ObjectTag::BULLET;

        position = startPos;
        rotation = startRotation;
        scale = Vector2(1.f, 1.f);
        texture = CreateTexture(renderer);

        speed = 500.0f;
        lifetime = 0.0f;
        maxLifetime = 2.0f;

        float mathAngle = (rotation - 90.0f) * (3.141592f / 180.0f);

        velocity.x = std::cos(mathAngle) * speed;
        velocity.y = std::sin(mathAngle) * speed;

        hitbox = { position.x, position.y, 8.0f * scale.x, 8.0f * scale.y };
    }

    ~Projectile() {}
};