#pragma once
#include "Scene.h"

class GamePlayScene : public Scene {

public:

	GamePlayScene() : Scene() {}

	void Start(SDL_Renderer* rend) override;
	void Update(float dt) override;
	void Render(SDL_Renderer* rend) override;
	void Exit() override;

	float spawnTimer = 0.0f;
	float timeBetweenSpawns = 3.0f;

};