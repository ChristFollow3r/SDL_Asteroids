            #include "Spaceship.h"


            SDL_Texture* Spaceship::CreateTexture(SDL_Renderer* renderer) {

                SDL_Surface* surf = IMG_Load("resources/asteroids_spritesheet.png");

                if (surf == nullptr) { std::cout << "Error creating surface:" << SDL_GetError() << std::endl; }
                SDL_Texture* textureTmp = SDL_CreateTextureFromSurface(renderer, surf);

                if (textureTmp == nullptr) { std::cout << "Error creating texture:" << SDL_GetError() << std::endl; }

                SDL_FreeSurface(surf);
                return textureTmp;
            }

            void Spaceship::Render(SDL_Renderer* renderer) {

                SDL_Rect source{ 0, 0, 32, 40 };

                SDL_Rect destination{ position.x, position.y, source.w * scale.x, source.h * scale.y };

                SDL_RenderCopyEx(renderer, texture, &source, &destination, rotation, nullptr, SDL_FLIP_NONE);
            }


            void Spaceship::Update(float dt) {

                int screenWidth = 800; // Suposo que axio ho podria possar a la clase virtual o a utils
                int screenHeight = 600;

                // ROTATTION BULLSHIT


                float shipCenterX = position.x + ((32.0f * scale.x) / 2.0f);
                float shipCenterY = position.y + ((40.0f * scale.y) / 2.0f);

                float mouseX = static_cast<float>(IM.GetMouseX());
                float mouseY = static_cast<float>(IM.GetMouseY());

                float deltaX = mouseX - shipCenterX;
                float deltaY = mouseY - shipCenterY;

                float angleRadians = std::atan2(deltaY, deltaX); // Ni idea de com funciona aixo, mho ha dit la IA.
                this->rotation = angleRadians * (180.0f / 3.141592f);
                this->rotation += 90.f; // Aixo es pq la nau miri al ratoli

                // MOVEMENT

                if (IM.GetKey(SDLK_w, HOLD)) { // PUTAS MATES DE MERDA DSE SUPOSA QUE HEM DE APENDRE LLIBRERIA GRAFICA NO A 
                    // CONATRUIR UN FOKING ROCKET MAAN

                    float forwardX = std::cos(angleRadians);
                    float forwardY = std::sin(angleRadians);

                    this->velocity.x += forwardX * impulseForce * dt;
                    this->velocity.y += forwardY * impulseForce * dt;
                }

                this->velocity.x *= 0.99f;
                this->velocity.y *= 0.99f;

                this->position.x += this->velocity.x * dt;
                this->position.y += this->velocity.y * dt;

                this->hitbox.x = this->position.x;
                this->hitbox.y = this->position.y;

                if (position.x > screenWidth + 50.0f) position.x = -50.0f; // Teleport shit
                else if (position.x < -50.0f) position.x = screenWidth + 50.0f; // Igualment aio crec que es una mica inutil perque
                // quan treus el ratoli fora de la pantalla sdl deixa de pillar la posicio del ratoli, i no tinc ni idea de com
                // arreglar-ho

                if (position.y > screenHeight + 50.0f) position.y = -50.0f;
                else if (position.y < -50.0f) position.y = screenHeight + 50.0f;

                // SHOOTING

                if (IM.GetKey(SDLK_SPACE, DOWN)) {

                    worldShit->push_back(std::make_unique<Projectile>(cachedRenderer, position, rotation));

                    // He cambiat com funciona pero deixo aqui el meu comentari d'abans

                    // bullets.push_back(std::move(bullet)); // Es fa move amb els unique ptrs pq no poden haveri copies
                    // d'un unique ptr, llavons si vols utilitzar el ptr a una altre part del codi,
                    // com ara, que el disparo, pero necessito guardarlo a algun lloc perque si el deixo aqui al moment que surti del scope 
                    // d'aquest if statement la palmará, el possem al vector que te el spaceship amb el std::move().
                }

                // for (auto& bullet : bullets) bullet->Update(dt);

                // for (int i = bullets.size() - 1; i >= 0; i--) if (bullets[i]->IsDead()) bullets.erase(bullets.begin() + i);
            }