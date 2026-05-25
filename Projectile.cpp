#include "Projectile.h"
#include <cmath>

SDL_Texture* Projectile::CreateTexture(SDL_Renderer* renderer) {

    SDL_Surface* surf = IMG_Load("resources/asteroids_spritesheet.png");
    SDL_Texture* textureTmp = SDL_CreateTextureFromSurface(renderer, surf);

    if (surf == nullptr) { std::cout << "Error creating surface:" << SDL_GetError() << std::endl; }
    if (textureTmp == nullptr) { std::cout << "Error creating texture:" << SDL_GetError() << std::endl; }

    SDL_FreeSurface(surf);
    return textureTmp;
}

void Projectile::Update(float dt) {

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    this->hitbox.x = this->position.x;
    this->hitbox.y = this->position.y;

    lifetime += dt;
}

void Projectile::Render(SDL_Renderer* renderer) {

    SDL_Rect source{ 34, 32, 8, 8 }; // Aixo de comptar pixels Marti es una guarrada maxima
    // També tinc un dubte a ver si mel pots respondre a la correció:
    // Com havies deixat el gameobject i com está la nau, i ara amb les bales, cada cop que es crea un d'aquests
    // tetes, s'està tornant a carregar la mateixa imatge per contar pixels. No seria millor guardar-la a gameEngine
    // o a una classe sprites i carregar-la nomes un cop i utilitzar-la a tot arreu?

    SDL_Rect destination{ position.x, position.y, source.w * scale.x, source.h * scale.y };

    SDL_RenderCopyEx(renderer, texture, &source, &destination, rotation, nullptr, SDL_FLIP_NONE);
}