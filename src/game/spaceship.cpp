#pragma once

#include "../engine/application.h"
#include "../engine/keyboard.h"
#include "../engine/sprite.h"
#include "spaceship_engine_fire.cpp"

#define MAX_VELOCITY 5
#define VELOCITY_STEP 0.1
#define VELOCITY_FRICTION 0.1

class Spaceship : public Sprite {
private:
    float x_velocity = 0;
    SpaceshipEngineFire* engine_fire = nullptr;

public:
    Spaceship(SpaceshipEngineFire* engine_fire) : Sprite("../assets/img/hand_made_spaceship.bmp") {
        this->engine_fire = engine_fire;

        *this->m_width = 60;
        *this->m_height = 60;
        *this->m_x = (this->m_application->getWidth() - 60) / 2;
        *this->m_y = this->m_application->getHeight() - 90;
    }

    void onUpdate(Uint64 delta) override {
        if (Keyboard::isKeyDown(SDLK_LEFT)) {
            if (this->x_velocity > -MAX_VELOCITY) {
                this->x_velocity -= VELOCITY_STEP;
            }
        } else if (Keyboard::isKeyDown(SDLK_RIGHT)) {
            if (this->x_velocity < MAX_VELOCITY) {
                this->x_velocity += VELOCITY_STEP;
            }
        } else if (!Keyboard::isKeyDown(SDLK_LEFT) && !Keyboard::isKeyDown(SDLK_RIGHT)) {
            if (abs(x_velocity) < VELOCITY_FRICTION) {
                this->x_velocity = 0;
            }
            if (this->x_velocity > 0) {
                this->x_velocity -= VELOCITY_FRICTION;
            } else if (this->x_velocity < 0) {
                this->x_velocity += VELOCITY_FRICTION;
            }
        }

        if (this->x_velocity != 0) {
            float new_x = *this->m_x + this->x_velocity;
            *this->m_x = new_x;
            *this->engine_fire->m_x = new_x + 22;
        }
    }
};
