#pragma once
#include "GameObject.h"
#include "Utils.h"

enum class AsteroidSize { BIG, MEDIUM, SMALL };

class Asteroid : public GameObject {

private:

    AsteroidSize size;
    float AsteroidMaxLifeSpan;
    SDL_Texture* CreateTexture(SDL_Renderer* renderer);

public:


    float AsteroidLifeTime = 0.0f; // Default value per si acas; mha dit la IA qeu si no ho posso c++ li assignara un valor garbage
    // que hi hagi per el codi

    Asteroid(SDL_Renderer* renderer, AsteroidSize size) : GameObject(renderer) { // Top 10 ugly constructors

        int screenWidth = 800;
        int screenHeight = 600;

        tag = ObjectTag::ASTEROID;

        int corner = rand() % 4;
        float speed = 50.0f + (rand() % 100);

        texture = CreateTexture(renderer);
        this->size = size;
        rotation = 0.0f;

        if (size == AsteroidSize::BIG) {
            scale = Vector2(3.0f, 3.0f);
            AsteroidMaxLifeSpan = 30.0f;
        }

        else if (size == AsteroidSize::MEDIUM) {
            scale = Vector2(2.0f, 2.0f);
            AsteroidMaxLifeSpan = 24.0f;
        }

        else {
            scale = Vector2(1.0f, 1.0f);
            AsteroidMaxLifeSpan = 16.0f;
        }


        if (corner == 0) {
            position = Vector2(rand() % screenWidth, -100.0f);
            velocity = Vector2((rand() % 100) - 50.0f, speed);
        }

        else if (corner == 1) {
            position = Vector2(screenWidth + 100.0f, rand() % screenHeight);
            velocity = Vector2(-speed, (rand() % 100) - 50.0f);
        }

        else if (corner == 2) {
            position = Vector2(rand() % screenWidth, screenHeight + 100.0f);
            velocity = Vector2((rand() % 100) - 50.0f, -speed);
        }

        else {
            position = Vector2(-100.0f, rand() % screenHeight);
            velocity = Vector2(speed, (rand() % 100) - 50.0f);
        }
    }

    void Render(SDL_Renderer* renderer) override;
    void Update(float dt) override;

    AsteroidSize GetSize() { return size; }
    float GetLifeSpan() { return AsteroidMaxLifeSpan; }
};