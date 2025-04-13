#pragma once

#include "../engine/__engine.h"
#include "spaceship_missile.cpp"

class MissilesView : public WorldObject {
    Uint64 lastMissileSpawnTime = 0;
    const Uint64 missileSpawnInterval = 500;

public:
    std::vector<SpaceshipMissile*> missiles_list;

    void init() {
        for (auto missile : missiles_list) {
            this->removeObject(missile);
            delete missile;
        }
        missiles_list.clear();
        this->lastMissileSpawnTime = 0;
    }

    void deleteMissile(SpaceshipMissile* missile) {
        this->removeObject(missile);
        this->missiles_list.erase(
                 std::remove(this->missiles_list.begin(), this->missiles_list.end(), missile),
                 this->missiles_list.end()
        );
        delete missile;
    }

    void update(Uint64 delta, SpaceshipView* spaceship) {
        if (MouseAndKeyboard::isKeyDown(SDLK_SPACE)) {
            if (this->lastMissileSpawnTime + this->missileSpawnInterval < delta) {
                SpaceshipMissile* missile = new SpaceshipMissile();
                this->addObject(missile);
                this->missiles_list.push_back(missile);
                *missile->m_x = *spaceship->m_x + *spaceship->m_width / 2 - *missile->m_width / 2;
                *missile->m_y = *spaceship->m_y;
                missile->setTargetPosition(
                    (float)*MouseAndKeyboard::mouse_x,
                    (float)*MouseAndKeyboard::mouse_y
                );
                this->lastMissileSpawnTime = delta;
            }
        }

        // check for out of screen missiles
        for (auto missile : this->missiles_list) {
            if (*missile->m_y + *missile->m_height < 0) {
                Logger::debug("delete missile");
                this->deleteMissile(missile);
            }
        }
    }
};
