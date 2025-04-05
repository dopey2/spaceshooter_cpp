#include "text.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "application.h" // CHECK if omited -> error: invalid use of incomplete type 'class Application'

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
        this->texture = nullptr;
        this->load(this->m_application->scene_manager->getRenderer());
    }
}

void Text::setX(float x) {
    WorldObject::setX(x);
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->x = x;
    }
}

void Text::setY(float y) {
    WorldObject::setY(y);
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->y = y;
    }
}

void Text::setWidth(float width) {
    WorldObject::setWidth(width);
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->w = width;
    }
}

void Text::setHeight(float height) {
    WorldObject::setHeight(height);
    if (this->m_target_rect != nullptr) {
        this->m_target_rect->h = height;
    }
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


    // if the width is not initialized use the texture original size
    if (this->m_width == nullptr) {
        this->m_width = (float*) malloc(sizeof(float));
        *this->m_width = texture_width;
    }

    // if the height is not initialized use the texture original size
    if (this->m_height == nullptr) {
        this->m_height = (float*) malloc(sizeof(float));
        *this->m_height = texture_height;
    }

    if(this->m_x == nullptr) {
        this->m_x = (float*) malloc(sizeof(float));
        *this->m_x = (renderer_w - *this->m_width) / 2;
    }

    if(this->m_y == nullptr) {
        this->m_y = (float*) malloc(sizeof(float));
        *this->m_y = (renderer_h - *this->m_height) / 2;
    }

    m_target_rect = new SDL_FRect({
            *this->m_x,
            *this->m_y,
            *this->m_width,
            *this->m_height
    });
}

void Text::render(SDL_Renderer *renderer) {
    if(this->texture == nullptr) {
        this->load(renderer);
    }
    SDL_RenderTexture(renderer, texture, NULL, m_target_rect);
}
