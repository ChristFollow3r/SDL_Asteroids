#pragma once

#include "Scene.h"

class MenuScene : public Scene {

public:
	MenuScene() : Scene() {}

	void Start(SDL_Renderer* rend) override {
	
		finished = false;
		targetScene = "";

		std::cout << "Press space to play!\n";
	};


	void Update(float dt) override {
	
		if (IM.GetKey(SDLK_SPACE, DOWN)) {
			targetScene = "Gameplay";
			finished = true;
		}
	};
	void Render(SDL_Renderer* rend) override {};
	void Exit() override {};

};