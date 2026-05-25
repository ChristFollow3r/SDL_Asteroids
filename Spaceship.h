#pragma once
#include "GameObject.h"
#include "InputManager.h"
#include "Projectile.h"
#include <vector>
#include <memory>
#include <cmath>
#include <iostream>

class Spaceship : public GameObject {

private:

    float impulseForce = 134.0f;
    int maxHP = 3;

    SDL_Renderer* cachedRenderer;
    SDL_Texture* CreateTexture(SDL_Renderer* renderer);

    // std::vector<std::unique_ptr<Projectile>> bullets;
    std::vector<std::unique_ptr<GameObject>>* worldShit; // Perque com les bales les creava dintre del spaceship
    // el vector de objectes no tenia ni idea de que estavan alla, nomes sabia que hi ha un spaceship


public:

    int currentHP;
    int totalPoints;

    Spaceship(SDL_Renderer* renderer, std::vector<std::unique_ptr<GameObject>>* objects) : GameObject(renderer) {

        worldShit = objects;
        tag = ObjectTag::SPACESHIP;

        currentHP = maxHP;
        totalPoints = 0;

        position = Vector2(250.0f, 250.0f);
        rotation = 0.0f;
        scale = Vector2(1.f, 1.f);
        texture = CreateTexture(renderer);
        cachedRenderer = renderer;

        hitbox = { position.x, position.y, 32.0f * scale.x, 40.0f * scale.y };

    }

    ~Spaceship() {}

    void TakeDamage();
    void AddPoints();

    void Render(SDL_Renderer* renderer) override;
    void Update(float dt) override;
};