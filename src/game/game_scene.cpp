#pragma once

#include "../engine/__engine.h"
#include "../engine/mouse_keyboard.h"
#include "asteroid.cpp"
#include "spaceship_missile.cpp"
#include "spaceship_view.cpp"

#define COLLISION_OFFSET 4

class GameScene : public Scene {
private:
    SpaceshipView* m_spaceship = nullptr;
    std::vector<Asteroid*> asteroids_list;
    std::vector<SpaceshipMissile*> missiles_list;

    Uint64 lastAsteroidSpawnTime = -1000;
    Uint64 asteroidSpawnInterval = 4000;

    Uint64 lastMissileSpawnTime = 0;
    Uint64 missileSpawnInterval = 500;

public:
    GameScene() {
        Sprite* background = new Sprite("../assets/img/bg.bmp");
        this->addObject(background);

        *background->m_width = this->application->getWidth();
        *background->m_height = this->application->getHeight();

        this->m_spaceship = new SpaceshipView();
        this->addObject(this->m_spaceship);
    }

    void deleteMissile(SpaceshipMissile* missile) {
        this->removeObject(missile);
        this->missiles_list.erase(
                 std::remove(this->missiles_list.begin(), this->missiles_list.end(), missile),
                 this->missiles_list.end()
        );
        delete missile;
    }

    void handleMissiles(Uint64 delta) {
        if (MouseAndKeyboard::isKeyDown(SDLK_SPACE)) {
            if (this->lastMissileSpawnTime + this->missileSpawnInterval < delta) {
                SpaceshipMissile* missile = new SpaceshipMissile();
                this->addObject(missile);
                this->missiles_list.push_back(missile);
                *missile->m_x = *this->m_spaceship->m_x + *this->m_spaceship->m_width / 2 - *missile->m_width / 2;
                *missile->m_y = *this->m_spaceship->m_y;
                missile->setTargetPosition(
                    (float)*MouseAndKeyboard::mouse_x,
                    (float)*MouseAndKeyboard::mouse_y
                );
                this->lastMissileSpawnTime = delta;
            }
        }

        for (auto missile : this->missiles_list) {
            if (*missile->m_y + *missile->m_height < 0) {
                Logger::debug("delete missile");
                this->deleteMissile(missile);
            }
        }
    }

    void handleAsteroids(Uint64 delta) {
        // Spawn new asteroid
        if (lastAsteroidSpawnTime + asteroidSpawnInterval < delta) {
            this->lastAsteroidSpawnTime = delta;
            Asteroid* asteroid = new Asteroid();
            this->addObject(asteroid);
            this->asteroids_list.push_back(asteroid);
        }


        // Update asteroids
        for (auto asteroid : this->asteroids_list) {
            asteroid->updateAsteroidPosition();

            if (asteroid->isColliding(this->m_spaceship, COLLISION_OFFSET)) {
                Logger::debug("Collision " + SDL_GetTicks());
            }

            if (asteroid->isOutOfScreen()) {
                this->removeObject(asteroid);
                this->asteroids_list.erase(
                    std::remove(this->asteroids_list.begin(), this->asteroids_list.end(), asteroid),
                    this->asteroids_list.end()
                );
                delete asteroid;
            }

            for (auto missile : this->missiles_list) {
                if (asteroid->isColliding(missile, COLLISION_OFFSET)) {
                    asteroid->destroyAsteroid();
                    this->deleteMissile(missile);
                }
            }
        }
    }


    void onUpdate(Uint64 delta) override {
        this->handleMissiles(delta);
        this->handleAsteroids(delta);
    }
};