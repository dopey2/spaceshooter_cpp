#include "text.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

Text::Text(char *fontFilePath, char *text, float fontSize) {
    this->m_font_file_path = fontFilePath;
    this->m_text = text;
    this->m_font_size = fontSize;
    this->m_text_color = new SDL_Color({255, 255, 255, SDL_ALPHA_OPAQUE});
}

Text::~Text() {
    SDL_DestroyTexture(texture);
    texture = nullptr;
}


void Text::setColor(SDL_Color *color) {
    if (
        this->m_text_color->a == color->a &&
        this->m_text_color->r == color->r &&
        this->m_text_color->g == color->g &&
        this->m_text_color->b == color->b) {
        return;
    }

    this->m_text_color = color;

    if (this->texture != nullptr) {
        this->texture = nullptr;
    }
}

void Text::setX(float x) {
    this->m_x = x;
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->x = x;
    }
}

void Text::setY(float y) {
    this->m_y = y;
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->y = y;
    }
}

void Text::setWidth(float width) {
    this->m_width = width;
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->w = width;
    }
}

void Text::setHeight(float height) {
    this->m_height = height;
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->h = height;
    }
}

void Text::load(SDL_Renderer *renderer) {
    TTF_Font *font = TTF_OpenFont(this->m_font_file_path, m_font_size);

    if (!font) {
        SDL_Log("Couldn't open font: %s\n", SDL_GetError());
    }


    SDL_Surface *text_surface = TTF_RenderText_Blended(font, "Hello World!", 0, *m_text_color);

    if (text_surface) {
        texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        SDL_DestroySurface(text_surface);
        TTF_CloseFont(font);
    }

    if (!texture) {
        SDL_Log("Couldn't create text: %s\n", SDL_GetError());
    }

    int renderer_w = 0;
    int renderer_h = 0;
    SDL_GetRenderOutputSize(renderer, &renderer_w, &renderer_h);
    SDL_GetTextureSize(texture, &this->m_width, &this->m_height);

    this->m_x = (renderer_w - this->m_width) / 2;
    this->m_y = (renderer_h - this->m_height) / 2;

    m_target_rect = new SDL_FRect({this->m_x, this->m_y, this->m_width, this->m_height});
}

void Text::render(SDL_Renderer *renderer) {
    if (texture == nullptr) {
        this->load(renderer);
    }

    SDL_RenderTexture(renderer, texture, NULL, m_target_rect);
}
