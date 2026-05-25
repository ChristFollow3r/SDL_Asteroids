#include "GameplayScene.h"
#include "Spaceship.h"
#include "Asteroid.h"

void GamePlayScene::Start(SDL_Renderer* renderer) { 

	Scene::Start(renderer);
	objects.push_back(std::make_unique<Spaceship>(renderer, &objects));
	objects.push_back(std::make_unique<Asteroid>(renderer, AsteroidSize::SMALL));
	objects.push_back(std::make_unique<Asteroid>(renderer, AsteroidSize::MEDIUM));
}

void GamePlayScene::Update(float dt) {

	Scene::Update(dt);

	spawnTimer += dt;

	if (spawnTimer >= timeBetweenSpawns) {

		AsteroidSize randomSize = static_cast<AsteroidSize>(rand() % 3);
		objects.push_back(std::make_unique<Asteroid>(sceneRenderer, randomSize));

		spawnTimer = 0.0f;

		if (timeBetweenSpawns > 2.0f) { timeBetweenSpawns -= 0.05f; }
	}


	// Detectar colisiones
	for (int i = 0; i < objects.size(); i++) { // Segur que hi han maneras mes eficients de fer aixo pero bueno funciona

		for (int j = 0; j < objects.size(); j++) {

			SDL_FRect hitboxA = objects[i]->GetHitbox();
			SDL_FRect hitboxB = objects[j]->GetHitbox();

			SDL_Rect hitboxAInt = {
				static_cast<int>(hitboxA.x),
				static_cast<int>(hitboxA.y),
				static_cast<int>(hitboxA.w),
				static_cast<int>(hitboxA.h)
			};

			SDL_Rect hitboxBInt = {
				static_cast<int>(hitboxB.x),
				static_cast<int>(hitboxB.y),
				static_cast<int>(hitboxB.w),
				static_cast<int>(hitboxB.h)
			};

			if (SDL_HasIntersection(&hitboxAInt, &hitboxBInt)) {

				ObjectTag tagA = objects[i]->GetTag();
				ObjectTag tagB = objects[j]->GetTag();

				if ((tagA == ObjectTag::BULLET && tagB == ObjectTag::ASTEROID) || 
					(tagA == ObjectTag::ASTEROID && tagB == ObjectTag::BULLET)) {

					objects[i]->Kill();
					objects[j]->Kill();

					std::cout << "Asteroid destroyed! 50 points\n";

				}

				else if ((tagA == ObjectTag::SPACESHIP && tagB == ObjectTag::ASTEROID) ||
					(tagA == ObjectTag::ASTEROID && tagB == ObjectTag::SPACESHIP)) {

					std::cout << "Player has been hit!\n";

					if (tagA == ObjectTag::ASTEROID) objects[i]->Kill();
					if (tagB == ObjectTag::ASTEROID) objects[j]->Kill();

				}
			}

		}
	}

	// Matar coses
	for (int i = objects.size() - 1; i >= 0; i--) if (objects[i]->IsDead()) objects.erase(objects.begin() + i);

}

void GamePlayScene::Render(SDL_Renderer* rend) {
	Scene::Render(rend);
}

void GamePlayScene::Exit() {
}