#include "sprite.h"
#include "assets_loader.h"
#include <SDL3/SDL.h>

Sprite::Sprite(const std::string& bmpFilePath) { this->m_bmp_file_path = bmpFilePath; }

Sprite::~Sprite() {
    if (this->m_texture != nullptr) {
        this->m_texture = nullptr;
    }

    delete m_source_rect;
    delete m_target_rect;
}

void Sprite::setAlpha(const float alpha) {
    this->m_alpha = alpha;
    SDL_SetTextureAlphaMod(this->m_texture, static_cast<Uint8>(this->m_alpha * 255));
}

void Sprite::load(SDL_Renderer* renderer) {
    if (this->m_texture == nullptr) {
        this->m_texture = AssetsLoaders::loadTexture(renderer, m_bmp_file_path);
        SDL_SetTextureAlphaMod(this->m_texture, static_cast<Uint8>(this->m_alpha * 255));

        // set dimension from texture if not manually setted
        // this allow pre setting the dimension before adding the object in the
        // tree/graph
        if (this->m_width == 0)
            this->m_width = static_cast<float>(m_texture->w);
        if (this->m_height == 0)
            this->m_height = static_cast<float>(m_texture->h);

        this->m_target_rect = new SDL_FRect({this->m_x, this->m_y, this->m_width, this->m_height});
    }
}

void Sprite::render(SDL_Renderer* const renderer, const float parent_x, const float parent_y) {
    if (this->m_texture == nullptr) {
        this->load(renderer);
    }

    this->m_target_rect->x = this->m_x + parent_x;
    this->m_target_rect->y = this->m_y + parent_y;
    this->m_target_rect->w = this->m_width;
    this->m_target_rect->h = this->m_width;

    SDL_RenderTextureRotated(
        renderer, this->m_texture, this->m_source_rect, this->m_target_rect, this->m_rotation, nullptr, SDL_FLIP_NONE
    );
}
