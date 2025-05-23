#pragma once

#include "../engine/__engine.h"
#include "spaceship_aim_laser.cpp"

#define MAX_VELOCITY 5
#define VELOCITY_STEP 0.1
#define VELOCITY_FRICTION 0.1

class SpaceshipView : public WorldObject {
private:
    bool is_game_over = false;
    float x_velocity = 0;

    Sprite *spaceship_sprite = nullptr;
    SpriteAnimation *engine_fire_animations = nullptr;
    SpaceshipAimLaser* aim_laser = nullptr;

public:
    SpaceshipView() {
        this->name = "missile_view";

        // view
        *this->m_width = 60;
        *this->m_height = 60;

        // spaceship sprite
        this->spaceship_sprite = new Sprite("../assets/img/hand_made_spaceship.bmp");
        *this->spaceship_sprite->m_width = 60;
        *this->spaceship_sprite->m_height = 60;

        // engine fire animation
        this->engine_fire_animations = new SpriteAnimation("../assets/img/fire_bullet_default.bmp");
        this->engine_fire_animations->addFrameFromTexture(new SDL_FRect({416, 48, 16, 16}));
        this->engine_fire_animations->addFrameFromTexture(new SDL_FRect({432, 48, 16, 16}));
        this->engine_fire_animations->addFrameFromTexture(new SDL_FRect({448, 48, 16, 16}));
        this->engine_fire_animations->addFrameFromTexture(new SDL_FRect({464, 48, 16, 16}));
        *this->engine_fire_animations->m_width = 16;
        *this->engine_fire_animations->m_height = 16;
        *this->engine_fire_animations->m_x = 22;
        *this->engine_fire_animations->m_y = 60;
        *this->engine_fire_animations->m_rotation = 270;

        this->addObject(spaceship_sprite);
        this->addObject(engine_fire_animations);

        this->aim_laser = new SpaceshipAimLaser();
        this->addObject(aim_laser);
    }

    float getLaserTargetX() {
        return *this->m_x + (*this->m_width / 2) + this->aim_laser->getTargetX();
    }

    float getLaserTargetY() {
        return 0;
    }

    void init() {
        this->is_game_over = false;
        *this->m_x = (this->m_application->getWidth() - 60) / 2;
        *this->m_y = this->m_application->getHeight() - 90;
    }

    void setGameOver(bool game_over) {
        this->is_game_over = game_over;
    }

    void onUpdate(Uint64 delta) override {
        if (this->is_game_over) {
            return;
        }

        this->aim_laser->update(this->m_y);

        if (MouseAndKeyboard::isKeyDown(SDLK_Q)) {
            if (this->x_velocity > -MAX_VELOCITY) {
                this->x_velocity -= VELOCITY_STEP;
            }
        } else if (MouseAndKeyboard::isKeyDown(SDLK_D)) {
            if (this->x_velocity < MAX_VELOCITY) {
                this->x_velocity += VELOCITY_STEP;
            }
        } else if (
            !MouseAndKeyboard::isKeyDown(SDLK_Q) &&
            !MouseAndKeyboard::isKeyDown(SDLK_D)
        ) {
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
            if (
                (this->x_velocity < 0 && *this->m_x + *this->m_width / 2 <= 0) ||
                (this->x_velocity > 0 && *this->m_x + *this->m_width / 2 >= this->m_application->getWidth())
            ) {
                this->x_velocity = 0;
                return;
            }
            float new_x = *this->m_x + this->x_velocity;
            *this->m_x = new_x;
        }
    }
};
