#include "../engine/application.h"
#include "../engine/scene.h"
#include "../engine/sprite.h"
#include "spaceship.cpp"
#include "spaceship_engine_fire.cpp"
#include "asteroid.cpp"

class GameScene : public Scene {
private:
    Spaceship* m_spaceship = nullptr;
    SpaceshipEngineFire* m_spaceship_engine_fire = nullptr;
    std::vector<Asteroid*> asteroids_list;

    Uint64 lastSpawnTimeAsteroid = -1000;
    Uint64 spawnInterval = 4000;

public:
    GameScene() {
        Sprite* background = new Sprite("../assets/img/bg.bmp");
        this->addObject(background);

        *background->m_width = this->application->getWidth();
        *background->m_height = this->application->getHeight();

        this->m_spaceship_engine_fire = new SpaceshipEngineFire();
        this->addObject(this->m_spaceship_engine_fire);

        this->m_spaceship = new Spaceship(this->m_spaceship_engine_fire);
        this->addObject(this->m_spaceship);
    }

    void onUpdate(Uint64 delta) override {
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

            if (asteroid->isHittingTheSpaceship(this->m_spaceship)) {
                std::cout << "Collision " << SDL_GetTicks() << std::endl;
            }
        }
    }
};