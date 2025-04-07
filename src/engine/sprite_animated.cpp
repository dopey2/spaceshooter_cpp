#include "sprite_animated.h"


SpriteAnimated::SpriteAnimated(char* file_path) {
    this->m_bmp_file_path = file_path;
}

void SpriteAnimated::setX(float x) {
    WorldObject::setX(x);
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->x = x;
    }
}

void SpriteAnimated::setY(float y) {
    WorldObject::setY(y);
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->y = y;
    }
}

void SpriteAnimated::setWidth(float width) {
    WorldObject::setWidth(width);
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->w = width;
    }
}

void SpriteAnimated::setHeight(float height) {
    WorldObject::setHeight(height);
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->h = height;
    }
}

void SpriteAnimated::addFrameFromTexture(SDL_FRect* source_rect) {
    this->frames.push_back(source_rect);
}

void SpriteAnimated::load(SDL_Renderer *renderer) {
    if (this->m_texture == nullptr) {
        this->m_texture = loadTexture(renderer, m_bmp_file_path);


        if (this->m_x == nullptr) {
            this->m_x = (float*) malloc(sizeof(float));
            *this->m_x = 0;
        }

        if (this->m_y == nullptr) {
            this->m_y = (float*) malloc(sizeof(float));
            *this->m_y = 0;
        }

        if (this->m_rotation == nullptr) {
            this->m_rotation = (float*) malloc(sizeof(float));
            *this->m_rotation = 0;
        }

        // if the width is not initialized use the texture original size
        if (this->m_width == nullptr) {
            this->m_width = (float*) malloc(sizeof(float));
            *this->m_width = (float)this->m_texture->w;
        }
        if (this->m_height == nullptr) {
            this->m_height = (float*) malloc(sizeof(float));
            *this->m_height = (float)this->m_texture->h;
        }

        this->m_target_rect = new SDL_FRect({
            *this->m_x,
            *this->m_y,
            *this->m_width,
            *this->m_height
        });
    }
}

void SpriteAnimated::render(SDL_Renderer *renderer) {
    if (this->m_texture == nullptr) {
        this->load(renderer);
    }

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

    this->loop_per_frame++;
    if(this->loop_per_frame == this->loop_per_frame_count) {
        this->loop_per_frame = 0;
        this->frame_index++;
        if(this->frame_index >= this->frames.size()) {
            this->frame_index = 0;
        }
    }
}
