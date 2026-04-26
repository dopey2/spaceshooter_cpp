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
    // Use Uint64 from SDL, this is an SDL driven value
    Uint64 last_update_time = 0;

public:
    SpriteAnimation(const std::string &file_path);
    ~SpriteAnimation();
    void addFrameFromTexture(SDL_FRect* source_rect);
    void render(SDL_Renderer *renderer, float parent_x, float parent_y);
};