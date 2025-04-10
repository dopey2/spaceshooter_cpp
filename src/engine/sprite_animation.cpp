#include "sprite_animation.h"


SpriteAnimation::SpriteAnimation(char* file_path) : Sprite(file_path) {}

void SpriteAnimation::addFrameFromTexture(SDL_FRect* source_rect) {
    this->frames.push_back(source_rect);
}

void SpriteAnimation::render(SDL_Renderer *renderer, float parent_x, float parent_y) {
    if (this->m_texture == nullptr) {
        this->load(renderer);
    }

    this->m_target_rect->x += parent_x;
    this->m_target_rect->y += parent_y;

    SDL_FRect* source_rect = this->frames.at(this->frame_index);

    SDL_RenderTextureRotated(
        renderer,
        this->m_texture,
        source_rect,
        this->m_target_rect,
        *this->m_rotation,
        NULL,
        SDL_FLIP_NONE
    );

    this->m_target_rect->x -= parent_x;
    this->m_target_rect->y -= parent_y;

    int delta = SDL_GetTicks();

    if(delta > this->last_update_time + this->frame_update_interval) {
        this->frame_index++;
        this->last_update_time = delta;
        if(this->frame_index >= this->frames.size()) {
            this->frame_index = 0;
        }
    }
}
