#include "GameplayScene.h"
#include "Spaceship.h"
#include "Asteroid.h"

// Lo bo de utilitzar smart pointers es que jo ho puc possar tot a dintre del vector de gameobjects, i en el moment en el que
// trec algo del vector, com aquest pointer ha sortit del scope, es borra automaticament

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
	for (int i = 0; i < objects.size(); i++) { 

		for (int j = i + 1; j < objects.size(); j++) { // M'ha dit la IA que possar j = i + 1 marregla un problema de que 
			// S'imprimeixin dos cops els textos

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

					for (int k = 0; k < objects.size(); k++) {
						if (objects[k]->GetTag() == ObjectTag::SPACESHIP && !objects[k]->IsDead()) { // Pq no li sumi punts si ja la ha palmat
							Spaceship* playerShip = static_cast<Spaceship*>(objects[k].get());
							playerShip->AddPoints();
						}
					}
					std::cout << "\nAsteroid destroyed! 50 points\n";

				}

				else if ((tagA == ObjectTag::SPACESHIP && tagB == ObjectTag::ASTEROID) ||
						(tagA == ObjectTag::ASTEROID && tagB == ObjectTag::SPACESHIP)) {

					int shipIndex = tagA == ObjectTag::SPACESHIP ? i : j;
					int asteroidIndex = tagA == ObjectTag::ASTEROID ? i : j;

					Spaceship* playerShip = static_cast<Spaceship*>(objects[shipIndex].get());
					playerShip->TakeDamage();

					objects[asteroidIndex]->Kill();
				}

			}

		}
	}

	// Matar coses
	for (int i = objects.size() - 1; i >= 0; i--) if (objects[i]->IsDead()) objects.erase(objects.begin() + i);

	bool playerIsAlive = false; //

	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->GetTag() == ObjectTag::SPACESHIP) {
			playerIsAlive = true;
			break;
		}
	}

	if (!playerIsAlive) {
		targetScene = "HighScore";
		finished = true;
	}

}

void GamePlayScene::Render(SDL_Renderer* rend) {
	Scene::Render(rend);
}

void GamePlayScene::Exit() {
}