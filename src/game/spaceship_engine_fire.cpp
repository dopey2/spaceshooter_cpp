#pragma once

#include "../engine/sprite_animation.h"

class SpaceshipEngineFire : public SpriteAnimation {
public:
    SpaceshipEngineFire() : SpriteAnimation("../assets/img/fires.bmp") {
        this->load(this->m_application->scene_manager->getRenderer());
        this->addFrameFromTexture(new SDL_FRect({416, 48, 16, 16}));
        this->addFrameFromTexture(new SDL_FRect({432, 48, 16, 16}));
        this->addFrameFromTexture(new SDL_FRect({448, 48, 16, 16}));
        this->addFrameFromTexture(new SDL_FRect({464, 48, 16, 16}));
        this->addFrameFromTexture(new SDL_FRect({476, 48, 16, 16}));
        this->setWidth(32);
        this->setHeight(32);
        this->setX((this->m_application->getWidth() - 30) / 2);
        this->setY(this->m_application->getHeight() - 50);
        *this->m_rotation = 90;
    }
};
