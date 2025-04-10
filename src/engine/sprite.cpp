#include "sprite.h"
#include <SDL3/SDL.h>
#include <limits>
#include "application.h"
#include "assets_loader.h"

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

void Sprite::setAlpha(float alpha) {
    this->alpha = alpha;
    SDL_SetTextureAlphaMod(this->m_texture, this->alpha * 255);
}

void Sprite::load(SDL_Renderer *renderer) {
    if (this->m_texture == nullptr) {
        this->m_texture = AssetsLoaders::loadTexture(renderer, m_bmp_file_path);
        SDL_SetTextureAlphaMod(this->m_texture, this->alpha * 255);

        m_target_rect = new SDL_FRect({
            0,
            0,
            (float)m_texture->w,
            (float)m_texture->h
        });

        this->m_x = &m_target_rect->x;
        this->m_y = &m_target_rect->y;
        this->m_width = &m_target_rect->w;
        this->m_height = &m_target_rect->h;

        this->m_rotation = (float*) malloc(sizeof(float));
        *this->m_rotation = 0;
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