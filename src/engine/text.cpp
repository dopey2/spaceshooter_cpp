#include "text.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "application.h"


Text::Text(char *fontFilePath, char *text, float fontSize) {
    this->m_font_file_path = fontFilePath;
    this->m_text = text;
    this->m_font_size = fontSize;
    this->m_text_color = new SDL_Color({255, 255, 255, SDL_ALPHA_OPAQUE});
    this->load(m_application->scene_manager->getRenderer());
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
        this->savePrevTransform();
        this->texture = nullptr;
        this->load(this->m_application->scene_manager->getRenderer());
    }
}

void Text::savePrevTransform() {
    this->prev_x = *this->m_x;
    this->prev_y = *this->m_y;
    this->prev_width = *this->m_width;
    this->prev_height = *this->m_height;
}



// must also be called every time a changes occurs in the text content or properties.
// no need to be called if only x & y positions changes.
void Text::load(SDL_Renderer *renderer) {
    TTF_Font *font = TTF_OpenFont(this->m_font_file_path, m_font_size);

    if (!font) {
        SDL_Log("Couldn't open font: %s\n", SDL_GetError());
    }


    SDL_Surface *text_surface = TTF_RenderText_Blended(font, this->m_text, 0, *m_text_color);

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

    float texture_width = 0;
    float texture_height = 0;
    SDL_GetTextureSize(texture, &texture_width, &texture_height);

    this->m_target_rect = new SDL_FRect({
           (renderer_w - texture_width) / 2,
           (renderer_h - texture_height) / 2,
           texture_width,
           texture_height
    });

    this->m_x = &m_target_rect->x;
    this->m_y = &m_target_rect->y;
    this->m_width = &m_target_rect->w;
    this->m_height = &m_target_rect->h;

    if (prev_x != std::numeric_limits<float>::infinity()) {
        *this->m_x = prev_x;
    }

    if (prev_y != std::numeric_limits<float>::infinity()) {
        *this->m_y = prev_y;
    }

    if (prev_width != -1) {
        *this->m_width = prev_width;
    }

    if (prev_height != -1) {
        *this->m_height = prev_height;
    }
}

void Text::render(SDL_Renderer *renderer, float parent_x, float parent_y) {
    if(this->texture == nullptr) {
        this->load(renderer);
    }

    this->m_target_rect->x += parent_x;
    this->m_target_rect->y += parent_y;

    SDL_RenderTexture(renderer, texture, NULL, m_target_rect);

    this->m_target_rect->x -= parent_x;
    this->m_target_rect->y -= parent_y;
}
