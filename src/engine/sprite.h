#pragma once

#include <SDL3/SDL.h>
#include "world_object.h"
#include "texture.h"

class Sprite : public WorldObject {
protected:
    const char *m_bmp_file_path;
    SDL_Texture *m_texture = nullptr;
    // Describe the object position & size in the source file
    SDL_FRect *m_source_rect = nullptr;
    // Describe the object position & size for rendering
    SDL_FRect *m_target_rect = nullptr;
    float alpha = 1;

public:
    Sprite(const char *bmpFilePath);
    ~Sprite();
    void setAlpha(float alpha);
    void load(SDL_Renderer *renderer);
    void unload();
    void render(SDL_Renderer *renderer);
};
