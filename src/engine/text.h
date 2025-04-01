#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "world_object.h"

class Text : public WorldObject {
    private:
        char* m_font_file_path = nullptr;
        char* m_text = nullptr;
        float m_font_size = 16;
        SDL_Color* m_text_color = nullptr;
        SDL_FRect *m_target_rect = nullptr;
        SDL_Texture* texture = nullptr;


    public:
        Text(char* fontFilePath, char* text, float fontSize);
        ~Text();

        void setColor(SDL_Color *color);

        void setX(float x);
        void setY(float y);
        void setWidth(float width);
        void setHeight(float height);
        void load(SDL_Renderer* renderer);
        void render(SDL_Renderer* renderer);
};