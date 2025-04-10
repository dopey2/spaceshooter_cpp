#pragma once

#include "../engine/__engine.h"

class SpaceshipMissile : public SpriteAnimation {

public:
    SpaceshipMissile() : SpriteAnimation("../assets/img/fire_bullet_blue.bmp") {
        *this->m_width = 16;
        *this->m_height = 16;
        *this->m_x = 0;
        *this->m_y = 0;

        // this->addFrameFromTexture(new SDL_FRect({179, 131, 10, 10}));
        // this->addFrameFromTexture(new SDL_FRect({195, 131, 10, 10}));
        // this->addFrameFromTexture(new SDL_FRect({211, 131, 10, 10}));
        // this->addFrameFromTexture(new SDL_FRect({227, 131, 10, 10}));

        // this->addFrameFromTexture(new SDL_FRect({98, 196, 12, 12}));
        // this->addFrameFromTexture(new SDL_FRect({114, 196, 12, 12}));
        // this->addFrameFromTexture(new SDL_FRect({130, 196, 12, 12}));
        // this->addFrameFromTexture(new SDL_FRect({146, 196, 12, 12}));


        this->addFrameFromTexture(new SDL_FRect({98, 258, 12, 12}));
        this->addFrameFromTexture(new SDL_FRect({114, 258, 12, 12}));
        this->addFrameFromTexture(new SDL_FRect({130, 258, 12, 12}));
        this->addFrameFromTexture(new SDL_FRect({146, 258, 12, 12}));
    }

    void onUpdate(Uint64 delta) override {

    }
};
