#include "Asteroid.h"
#include <iostream>

SDL_Texture* Asteroid::CreateTexture(SDL_Renderer* renderer) {

    SDL_Surface* surf = IMG_Load("resources/asteroids_spritesheet.png");
    SDL_Texture* textureTmp = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_FreeSurface(surf);

    return textureTmp;
}

void Asteroid::Update(float dt) {

    int screenWidth = 800;
    int screenHeight = 600;

    this->AsteroidLifeTime += dt;
    if (this->AsteroidLifeTime >= AsteroidMaxLifeSpan) this->Kill();

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    rotation += 20.0f * dt;

    hitbox = { position.x, position.y, 32.0f * scale.x, 32.0f * scale.y };


    if (position.x > screenWidth + 50.0f) position.x = -50.0f; // Teleport shit
    else if (position.x < -50.0f) position.x = screenWidth + 50.0f;

    if (position.y > screenHeight + 50.0f) position.y = -50.0f;
    else if (position.y < -50.0f) position.y = screenHeight + 50.0f;

    this->hitbox.x = this->position.x;
    this->hitbox.y = this->position.y;
}

void Asteroid::Render(SDL_Renderer* renderer) {

    SDL_Rect source{ 41, 3, 32, 32 };
    SDL_Rect destination{ position.x, position.y, source.w * scale.x, source.h * scale.y };

    SDL_RenderCopyEx(renderer, texture, &source, &destination, rotation, nullptr, SDL_FLIP_NONE);
}