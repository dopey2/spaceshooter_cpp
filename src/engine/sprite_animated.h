#pragma once

#include <vector>
#include <SDL3/SDL.h>
#include "world_object.h"
#include "texture.h"

class SpriteAnimated : public WorldObject {
private:
    const char *m_bmp_file_path;
    SDL_Texture *m_texture = nullptr;
    std::vector<SDL_FRect*> frames;
    SDL_FRect *m_target_rect = nullptr;
    uint16_t frame_index = 0;
    uint16_t loop_per_frame = 0;
    uint16_t loop_per_frame_count = 3;

public:
    SpriteAnimated(char* file_path);
    void setX(float x);
    void setY(float y);
    void setWidth(float width);
    void setHeight(float height);
    void addFrameFromTexture(SDL_FRect* source_rect);
    void load(SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer);
};