#include "engine/__engine.h"
#include "engine/mouse_keyboard.h"
#include <array>
#include <cstdint>

enum MenuOptions : std::uint8_t {
    PLAY = 0,
    SETTINGS = 1,
    QUIT = 2
};

struct MenuItem {
    const MenuOptions value;
    const MenuOptions previousValue;
    const MenuOptions nextValue;
    const std::string label;
    Text* text = nullptr;
};

class MenuScene : public Scene {
private:
    SDL_Color selected_color = {200, 50, 50, SDL_ALPHA_OPAQUE};
    SDL_Color unselected_color = {255, 255, 255, SDL_ALPHA_OPAQUE};

    MenuOptions currentSelected = PLAY;

    std::array<MenuItem, 3> items = {{
        {PLAY,     QUIT,     SETTINGS, "Play"},
        {SETTINGS, PLAY,     QUIT,     "Settings"},
        {QUIT,     SETTINGS, PLAY,     "Quit"},
    }};

public:
    MenuScene() {
        float start_y = this->application->getHeightF() / 2.0f - 30.0f;

        for (size_t i = 0; i < items.size(); i++) {
            auto* text = new Text(AssetsLoaders::getAsset("font/Arial.ttf"), items[i].label, 24);
            items[i].text = text;
            this->addObject(text);
            text->m_x = (this->application->getWidthF() - text->m_width) / 2.0f;
            text->m_y = start_y + static_cast<float>(i) * 30.0f;
        }

        this->applyButtonStyles();
        this->setupKeyPressListener();
    };

    void setupKeyPressListener() {
        MouseAndKeyboard::addKeyPressListener([&](SDL_KeyboardEvent event) -> void {
            if (event.key == SDLK_UP) {
                // on press up
                this->currentSelected = this->items[this->currentSelected].previousValue;
            } else if (event.key == SDLK_DOWN) {
                // on press down
                this->currentSelected = this->items[this->currentSelected].nextValue;
            }

            this->applyButtonStyles();

            if (event.key == SDLK_RETURN) {
                if (this->currentSelected == PLAY) this->actionPlay();
                else if (this->currentSelected == SETTINGS) this->actionSettings();
                else if (this->currentSelected == QUIT) this->actionQuit();
            }
        });
    }

    void actionPlay()     {
         this->application->scene_manager->setActiveScene("game"); 
    }

    void actionSettings() {
        // not implemented yet
        // will be later used for:
        //  - key bindings
        //  - resolution
        //  - sound ON/OFF
     }

    void actionQuit() { 
        this->application->stop(); 
    }

    void applyButtonStyles() {
        for (auto& item : this->items) {
            item.text->setColor(item.value == this->currentSelected ? this->selected_color : this->unselected_color);
        }
    }
};
