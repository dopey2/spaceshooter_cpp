#include "../engine/application.h"
#include "../engine/scene.h"
#include "spaceship.cpp"
#include "spaceship_engine_fire.cpp"
#include "asteroid.cpp"

class GameScene : public Scene {
private:
    Spaceship* m_spaceship = nullptr;
    SpaceshipEngineFire* m_spaceship_engine_fire = nullptr;
    std::vector<Asteroid*> asteroids_list;

    Uint64 lastSpawnTimeAsteroid = -1000;
    Uint64 spawnInterval = 2000;

    SDL_Color* colorRed = new SDL_Color({255, 0, 0, SDL_ALPHA_OPAQUE});

public:
    GameScene() {
        this->m_spaceship_engine_fire = new SpaceshipEngineFire();
        this->addObject(this->m_spaceship_engine_fire);

        this->m_spaceship = new Spaceship(this->m_spaceship_engine_fire);
        this->addObject(this->m_spaceship);


        // todo disable update for inactive screen
        this->application->register_update_callback([=](Uint64 delta) -> void {
            this->onUpdate(delta);
        });
    }

    void onUpdate(Uint64 delta) {
        if (lastSpawnTimeAsteroid + spawnInterval < delta) {
            this->lastSpawnTimeAsteroid = delta;
            Asteroid* asteroid = new Asteroid();
            this->addObject(asteroid);
            this->asteroids_list.push_back(asteroid);
        }

        for (auto asteroid : this->asteroids_list) {
            asteroid->updateAsteroidPosition();
            if (asteroid->isOutOfScreen()) {
                this->removeObject(asteroid);
            }
        }
    }
};