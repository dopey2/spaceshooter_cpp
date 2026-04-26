#include "sprite_animation.h"


SpriteAnimation::SpriteAnimation(const std::string &file_path) : Sprite(file_path) {}

 SpriteAnimation::~SpriteAnimation() {
    for (auto frame : this->frames) {
        delete frame;
    }
    this->frames.clear();
}


void SpriteAnimation::addFrameFromTexture(SDL_FRect* source_rect) {
    this->frames.push_back(source_rect);
}

void SpriteAnimation::render(SDL_Renderer *renderer, float parent_x, float parent_y) {
    if (this->m_texture == nullptr) {
        this->load(renderer);
    }

    this->m_target_rect->x = this->m_x + parent_x;
    this->m_target_rect->y = this->m_y + parent_y;
    this->m_target_rect->w = this->m_width;
    this->m_target_rect->h = this->m_width;

    SDL_FRect* source_rect = this->frames.at(this->frame_index);

    SDL_RenderTextureRotated(
        renderer,
        this->m_texture,
        source_rect,
        this->m_target_rect,
        this->m_rotation,
        NULL,
        SDL_FLIP_NONE
    );

    Uint64 delta = SDL_GetTicks();

    if(delta > this->last_update_time + this->frame_update_interval) {
        this->frame_index++;
        this->last_update_time = delta;
        if(this->frame_index >= this->frames.size()) {
            this->frame_index = 0;
        }
    }
}
