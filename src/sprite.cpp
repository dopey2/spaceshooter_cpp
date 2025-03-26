#include <SDL3/SDL.h>
#include "world_object.cpp"
#include "texture.cpp"

class Sprite : public WorldObject {
private:
    const char *m_bmp_file_path;
    SDL_Texture *m_texture = nullptr;

    // Describe the object position & size in the source file
    const SDL_FRect *m_source_rect = nullptr;
    // Describe the object position & size for rendering
    const SDL_FRect *m_target_rect = nullptr;

public:
    Sprite(const char *bmpFilePath): WorldObject() {
        this->m_bmp_file_path = bmpFilePath;
    }

    void load(SDL_Renderer *renderer) {
        if (this->m_texture == nullptr) {
            this->m_texture = loadTexture(renderer, m_bmp_file_path);

            *this->width = (float)this->m_texture->w;
            *this->height = (float)this->m_texture->h;

            m_target_rect = new SDL_FRect({
                *this->x,
                *this->y,
                *this->width,
                *this->height
            });
        }
    }

    void unload() {
        if (this->m_texture != nullptr) {
            SDL_DestroyTexture(this->m_texture);
        }
    }


    void render(SDL_Renderer *renderer) {
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
};
