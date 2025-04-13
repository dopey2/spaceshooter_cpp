#include <limits>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "world_object.h"

class Text : public WorldObject {
    private:
        // this methods should not be available since a sprite cannot contain any children
        using WorldObject::children;
        using WorldObject::addObject;
        using WorldObject::removeObject;

        char* m_font_file_path = nullptr;
        char* m_text = nullptr;
        float m_font_size = 16;
        SDL_Color* m_text_color = nullptr;
        SDL_FRect *m_target_rect = nullptr;
        SDL_Texture* texture = nullptr;

        float prev_x = std::numeric_limits<float>::infinity();
        float prev_y = std::numeric_limits<float>::infinity();
        float prev_width = -1;
        float prev_height = -1;

        void savePrevTransform();

    public:
        Text(char* fontFilePath, char* text, float fontSize);
        ~Text();
        void setColor(SDL_Color *color);
        void load(SDL_Renderer* renderer);
        virtual void render(SDL_Renderer *renderer, float parent_x, float parent_y);
};