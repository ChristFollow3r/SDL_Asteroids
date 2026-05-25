#pragma once
#include "Utils.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

enum class ObjectTag { NONE, SPACESHIP, BULLET, ASTEROID };

class GameObject {

protected:

    float rotation;
    bool isDead = false;

    ObjectTag tag = ObjectTag::NONE; // La idea es utilitzar la funcio de SDL hasIntersectedWithRect (bueno aixi es a SDL3 ns com es 
    // diu a SDL2), i depenen del que ha xocat amb que matar a una cosa o a un altre. 

    Vector2 position;
    Vector2 scale;
    Vector2 velocity;

    SDL_Texture* texture;
    SDL_FRect hitbox;

public:

    GameObject(SDL_Renderer* renderer) {} 
    ~GameObject() {}

    virtual void Render(SDL_Renderer* renderer) = 0;
    virtual void Update(float dt) = 0;

    virtual void Kill() { isDead = true; }
    virtual bool IsDead() { return isDead; }

    SDL_FRect GetHitbox() { return hitbox; }
    ObjectTag GetTag() { return tag; }
};