#pragma once

#include "../engine/__engine.h"
#include "math.cpp"


#define DISTANCE_PER_FRAME 3

class SpaceshipMissile : public SpriteAnimation {
private:
    float velocity_x = 0;
    float velocity_y = 0;

public:
    SpaceshipMissile() : SpriteAnimation("../assets/img/fire_bullet_blue.bmp") {
        *this->m_width = 16;
        *this->m_height = 16;
        *this->m_x = 0;
        *this->m_y = 0;

        this->addFrameFromTexture(new SDL_FRect({98, 258, 12, 12}));
        this->addFrameFromTexture(new SDL_FRect({114, 258, 12, 12}));
        this->addFrameFromTexture(new SDL_FRect({130, 258, 12, 12}));
        this->addFrameFromTexture(new SDL_FRect({146, 258, 12, 12}));
    }

    void setTargetPosition(float target_x, float target_y) {
        float xdiff = target_x - *this->m_x;
        float ydiff = target_y - *this->m_y;
        auto [length, degree] = Math::cartesianToPolar(xdiff, ydiff);
        auto [step_x, step_y] = Math::polarToCartesian(DISTANCE_PER_FRAME, degree);
        this->velocity_x = step_x;
        this->velocity_y = step_y;
    }

    void onUpdate(Uint64 delta) override {
        *this->m_y += this->velocity_y;
        *this->m_x += this->velocity_x;
    }
};
