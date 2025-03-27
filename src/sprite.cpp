#include <SDL3/SDL.h>
#include "world_object.cpp"
#include "texture.cpp"

class Sprite : public WorldObject {
private:
    const char *m_bmp_file_path;
    SDL_Texture *m_texture = nullptr;

    // Describe the object position & size in the source file
    SDL_FRect *m_source_rect = nullptr;
    // Describe the object position & size for rendering
    SDL_FRect *m_target_rect = nullptr;

public:
    Sprite(const char *bmpFilePath): WorldObject() {
        this->m_bmp_file_path = bmpFilePath;
    }

    void setX(float x) {
        this->m_x = x;
        this->m_target_rect->x = x;
    }

    void setY(float x) {
        this->m_x = x;
        this->m_target_rect->y = y;
    }

    void setPosition(float x, float y) {
        this->m_x = x; this->m_y = y;
        this->m_target_rect->y = y;
    }

    void setWidth(float width) {
        this->m_width = width;
        this->m_target_rect->w = width;
    }

    void setHeight(float height) {
        this->m_height = height;
        this->m_target_rect->h = height;
    }

    void load(SDL_Renderer *renderer) {
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

    void unload() {
        if (this->m_texture != nullptr) {
            std::cout << "Destroy sprite texture";
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
