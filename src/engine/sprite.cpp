#include <SDL3/SDL.h>
#include "sprite.h"

Sprite::Sprite(const char *bmpFilePath) {
    this->m_bmp_file_path = bmpFilePath;
}

void Sprite::setX(float x) {
    this->m_x = x;
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->x = x;
    }
}

void Sprite::setY(float y) {
    this->m_y = y;
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->y = y;
    }
}

void Sprite::setPosition(float x, float y) {
    this->m_x = x; this->m_y = y;
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->x = x;
        this->m_target_rect->y = y;
    }
}

void Sprite::setWidth(float width) {
    this->m_width = width;
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->w = width;
    }
}

void Sprite::setHeight(float height) {
    this->m_height = height;
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->h = height;
    }

}

void Sprite::load(SDL_Renderer *renderer) {
    if (this->m_texture == nullptr) {
        this->m_texture = loadTexture(renderer, m_bmp_file_path);

        this->m_width = (float)this->m_texture->w;
        this->m_height = (float)this->m_texture->h;

        m_target_rect = new SDL_FRect({
            this->x,
            this->y,
            this->width,
            this->height
        });
    }
}

void Sprite::unload() {
    if (this->m_texture != nullptr) {
        std::cout << "Destroy sprite texture";
        SDL_DestroyTexture(this->m_texture);
    }
}


void Sprite::render(SDL_Renderer *renderer) {
    if (this->m_texture == nullptr) {
        this->load(renderer);
    }

    SDL_RenderTextureRotated(
        renderer,
        this->m_texture,
        this->m_source_rect,
        this->m_target_rect,
        0,
        NULL,
        SDL_FLIP_NONE
    );
}