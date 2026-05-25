#pragma once
#include "Scene.h"

class HighscoreScene : public Scene {

public:
	HighscoreScene() : Scene() {} // Els punts els tinc possats a Spaceship

	void Start(SDL_Renderer* rend) override {
		finished = false;
		targetScene = "";

		std::cout << "Thanks for playing!\nPress space to play again or esc to exxit the program\n";
	};
	void Update(float dt) override {
		if (IM.GetKey(SDLK_SPACE, DOWN)) {
			targetScene = "MainMenu";
			finished = true;
		}

		if (IM.GetKey(SDLK_ESCAPE, DOWN)) {
			exit(0);
		}
	};
	void Render(SDL_Renderer* rend) override {};
	void Exit() override {};

};