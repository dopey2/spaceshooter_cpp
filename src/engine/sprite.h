#pragma once

#include <string>
#include <SDL3/SDL.h>
#include "world_object.h"

class Sprite : public WorldObject {
private:
    // this methods should not be available since a sprite cannot contain any children
    using WorldObject::children;
    using WorldObject::addObject;
    using WorldObject::removeObject;

protected:
    std::string m_bmp_file_path;
    SDL_Texture *m_texture = nullptr;
    // Describe the object position & size in the source file
    SDL_FRect *m_source_rect = nullptr;
    // Describe the object position & size for rendering
    SDL_FRect *m_target_rect = nullptr;
    float alpha = 1;

public:
    Sprite(std::string bmpFilePath);
    ~Sprite();
    void setAlpha(float alpha);
    void load(SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer, float parent_x, float parent_y);
};
