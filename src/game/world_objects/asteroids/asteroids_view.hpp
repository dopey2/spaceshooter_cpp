#pragma once

#include <algorithm>
#include <memory>
#include "engine/__engine.h"
#include "./asteroid.hpp"
#include "../spaceship/spaceship_view.hpp"
#include "../spaceship/missiles_view.hpp"

class AsteroidsView : public WorldObject {
private:
    Uint64 lastAsteroidSpawnTime = 0;
    const Uint64 asteroidSpawnInterval = 4000;

    std::vector<Asteroid*> asteroids_list;

    Asteroid* spawnNewAsteroid() {
        auto asteroidOwner = std::make_unique<Asteroid>();
        auto asteroid = asteroidOwner.get();
        this->addObject(std::move(asteroidOwner));
        return asteroid;
    }


public:
    void init() {
        for (auto asteroid : asteroids_list) {
            this->removeObject(asteroid);
        }
        asteroids_list.clear();
        this->lastAsteroidSpawnTime = 0;
    }

    void update(Uint64 delta, MissilesView* missiles_view) {
        // Spawn new asteroid
        if (this->lastAsteroidSpawnTime + this->asteroidSpawnInterval < delta) {
            this->lastAsteroidSpawnTime = delta;
            auto asteroid = this->spawnNewAsteroid();
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
                continue;
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
            float additionalOffset = abs(spaceship->m_x - asteroid->m_x) / 2;
            if (asteroid->isColliding(spaceship, 8 + additionalOffset)) {
                return true;
            }
        }
        return false;
    }
};
