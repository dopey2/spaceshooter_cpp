#pragma once

#include "../engine/sprite_animation.h"

class SpaceshipEngineFire : public SpriteAnimation {
public:
    SpaceshipEngineFire() : SpriteAnimation("../assets/img/fires.bmp") {
        this->addFrameFromTexture(new SDL_FRect({416, 48, 16, 16}));
        this->addFrameFromTexture(new SDL_FRect({432, 48, 16, 16}));
        this->addFrameFromTexture(new SDL_FRect({448, 48, 16, 16}));
        this->addFrameFromTexture(new SDL_FRect({464, 48, 16, 16}));
        *this->m_width = 16;
        *this->m_height = 16;
        *this->m_x = (this->m_application->getWidth() - 16) / 2;
        *this->m_y = this->m_application->getHeight() - 34;
        *this->m_rotation = 270;
    }
};
