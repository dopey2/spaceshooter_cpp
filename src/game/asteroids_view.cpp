#pragma once

#include "../engine/__engine.h"
#include "asteroid.cpp"
#include "spaceship_view.cpp"
#include "missiles_view.cpp"

class AsteroidsView : public WorldObject {
private:
    Uint64 lastAsteroidSpawnTime = 0;
    const Uint64 asteroidSpawnInterval = 4000;

    std::vector<Asteroid*> asteroids_list;

public:
    void init() {
        for (auto asteroid : asteroids_list) {
            this->removeObject(asteroid);
            delete asteroid;
        }
        asteroids_list.clear();
        this->lastAsteroidSpawnTime = 0;
    }

    void update(Uint64 delta, MissilesView* missiles_view) {
        // Spawn new asteroid
        if (this->lastAsteroidSpawnTime + this->asteroidSpawnInterval < delta) {
            std::cout << "Spawn asteroid" << std::endl;
            this->lastAsteroidSpawnTime = delta;
            Asteroid* asteroid = new Asteroid();
            this->addObject(asteroid);
            this->asteroids_list.push_back(asteroid);
        }

        // Update asteroids
        for (auto asteroid : this->asteroids_list) {
            asteroid->updateAsteroidPosition();

            // check out of screen
            if (asteroid->isOutOfScreen()) {
                this->removeObject(asteroid);
                this->asteroids_list.erase(
                    std::remove(this->asteroids_list.begin(), this->asteroids_list.end(), asteroid),
                    this->asteroids_list.end()
                );
                delete asteroid;
            }

            // check collision with missiles
            for (auto missile : missiles_view->missiles_list) {
                if (asteroid->isColliding(missile, 4)) {
                    asteroid->destroyAsteroid();
                    missiles_view->deleteMissile(missile);
                }
            }
        }
    }

    bool isCollidingWithSpaceship(SpaceshipView* spaceship) {
        for (auto asteroid : this->asteroids_list) {
            if (asteroid->isColliding(spaceship, 4)) {
                return true;
            }
        }
        return false;
    }
};
