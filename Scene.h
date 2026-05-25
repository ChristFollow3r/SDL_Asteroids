#pragma once
#include "GameObject.h"
#include <vector>

class Scene {

protected:

	std::vector<std::unique_ptr<GameObject>> objects;

	SDL_Renderer* sceneRenderer;

	bool finished;
	std::string targetScene;

public:

	virtual void Start(SDL_Renderer* renderer) {
		finished = false;
		sceneRenderer = renderer;
	};

	virtual void Update(float dt) {
		for (int i = 0; i < objects.size(); i++) { 
			objects[i]->Update(dt);
		}
	}
	
	virtual void Render(SDL_Renderer* rend) {
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->Render(rend);
		}
	}

	virtual void Exit() = 0;

	bool IsFinished() { return finished; }
	std::string GetTargetScene() { return targetScene; }
};