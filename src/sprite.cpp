#include <SDL3/SDL.h>
#include "application.cpp"
#include "world_object.cpp"
#include "texture.cpp"

class Sprite: public WorldObject {
private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;

    // Describe the object position & size in the source file
    const SDL_FRect* source_rect = nullptr;
    // Describe the object position & size for rendering
    const SDL_FRect* target_rect = nullptr;

public:
    Sprite(const char* bmpFilePath) {
        Application* app = Application::_instance;

        this->renderer = app->_renderer;
        this->texture = loadTexture(renderer, bmpFilePath);

        *this->width = this->texture->w;
        *this->height = this->texture->h;

        target_rect = new SDL_FRect({
               *this->x,
               *this->y,
               *this->width,
               *this->height
        });
    }

    void render() {
        SDL_RenderTextureRotated(renderer, texture, this->source_rect, this->target_rect, 0, NULL, SDL_FLIP_NONE);
    }
};