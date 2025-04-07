#include <SDL3/SDL.h>
#include "sprite.h"
#include "application.h"

Sprite::Sprite(const char *bmpFilePath) {
    this->m_bmp_file_path = bmpFilePath;
    this->load(m_application->scene_manager->getRenderer());
}

Sprite::~Sprite() {
    if (this->m_texture != nullptr) {
        std::cout << "Destroying sprite texture" << std::endl;
        SDL_DestroyTexture(this->m_texture);
        this->m_texture = nullptr;
    }
}

void Sprite::setX(float x) {
    WorldObject::setX(x);
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->x = x;
    }
}

void Sprite::setY(float y) {
    WorldObject::setY(y);
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->y = y;
    }
}

void Sprite::setWidth(float width) {
    WorldObject::setWidth(width);
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->w = width;
    }
}

void Sprite::setHeight(float height) {
    WorldObject::setHeight(height);
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->h = height;
    }
}

void Sprite::setAlpha(float alpha) {
    this->alpha = alpha;
    SDL_SetTextureAlphaMod(this->m_texture, this->alpha * 255);
}

void Sprite::load(SDL_Renderer *renderer) {
    if (this->m_texture == nullptr) {
        this->m_texture = loadTexture(renderer, m_bmp_file_path);
        SDL_SetTextureAlphaMod(this->m_texture, this->alpha * 255);


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

        m_target_rect = new SDL_FRect({
            *this->m_x,
            *this->m_y,
            *this->m_width,
            *this->m_height
        });
    }
}

void Sprite::unload() {
    // if (this->m_texture != nullptr) {
    //     std::cout << "Destroy sprite texture";
    //     SDL_DestroyTexture(this->m_texture);
    // }
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
        *this->m_rotation,
        NULL,
        SDL_FLIP_NONE
    );
}