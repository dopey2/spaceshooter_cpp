#pragma once

#include "./spaceship_missile.hpp"
#include "engine/__engine.h"
#include <algorithm>
#include <memory>

class MissilesView : public WorldObject {
  private:
    Uint64 lastMissileSpawnTime = 0;
    const Uint64 missileSpawnInterval = 500;

    SpaceshipMissile* spawnNewMissile() {
        auto missileOwner = std::make_unique<SpaceshipMissile>();
        auto missile = missileOwner.get(); // non owning-ref
        this->addObject(std::move(missileOwner));
        return missile;
    }

  public:
    std::vector<SpaceshipMissile*> missiles_list;

    void init() {
        for (auto missile : missiles_list) {
            this->removeObject(missile);
        }
        missiles_list.clear();
        this->lastMissileSpawnTime = 0;
    }

    void deleteMissile(SpaceshipMissile* missile) {
        this->removeObject(missile);
        this->missiles_list.erase(
            std::remove(this->missiles_list.begin(), this->missiles_list.end(), missile), this->missiles_list.end()
        );
    }

    void update(Uint64 delta, SpaceshipView* spaceship) {
        if (MouseAndKeyboard::isKeyDown(SDLK_SPACE)) {
            if (this->lastMissileSpawnTime + this->missileSpawnInterval < delta) {
                auto missile = this->spawnNewMissile();
                this->missiles_list.push_back(missile);
                missile->m_x = spaceship->m_x + spaceship->m_width / 2 - missile->m_width / 2;
                missile->m_y = spaceship->m_y;
                missile->setTargetPosition(spaceship->getLaserTargetX(), spaceship->getLaserTargetY());
                this->lastMissileSpawnTime = delta;
            }
        }

        // check for out of screen missiles
        for (auto missile : this->missiles_list) {
            if (missile->m_y + missile->m_height < 0) {
                Logger::debug("deleted missile out of screen");
                this->deleteMissile(missile);
            }
        }
    }
};
