#pragma once

#include <vector>
#include <SDL3/SDL.h>
#include "world_object.h"
#include "sprite.h"

class SpriteAnimation : public Sprite {
private:
    std::vector<SDL_FRect*> frames;
    uint16_t frame_index = 0;
    uint16_t frame_update_interval = 50;
    uint16_t last_update_time = 0;

public:
    SpriteAnimation(char* file_path);
    void addFrameFromTexture(SDL_FRect* source_rect);
    void render(SDL_Renderer *renderer);
};