#include "engine/__engine.h"
#include <cstdint>

enum MenuOptions : std::uint8_t {
    PLAY = 0,
    SETTINGS = 1,
    QUIT = 2
};


class MenuScene : public Scene {
private:
    Text* menu_play_button = nullptr;
    Text* menu_settings_button = nullptr;
    Text* menu_quit_button = nullptr;

    SDL_Color selected_color = {200, 50, 50, SDL_ALPHA_OPAQUE};
    SDL_Color unselected_color = {255, 255, 255, SDL_ALPHA_OPAQUE};

    int8_t menu_choice = MenuOptions::PLAY;

public:
    MenuScene() {
        this->menu_play_button = new Text(AssetsLoaders::getAsset("font/Arial.ttf"), "Play", 24);
        this->menu_settings_button = new Text(AssetsLoaders::getAsset("font/Arial.ttf"), "Settings", 24);
        this->menu_quit_button = new Text(AssetsLoaders::getAsset("font/Arial.ttf"), "Quit", 24);

        this->addObject(menu_play_button);
        this->addObject(menu_settings_button);
        this->addObject(menu_quit_button);

        this->menu_play_button->m_x = (this->application->getWidthF() - menu_play_button->m_width) / 2;
        this->menu_settings_button->m_x = (this->application->getWidthF() - menu_settings_button->m_width) / 2;
        this->menu_quit_button->m_x = (this->application->getWidthF() - menu_quit_button->m_width) / 2;

        this->menu_play_button->m_y = this->application->getHeightF() / 2 - 30;
        this->menu_settings_button->m_y = this->application->getHeightF() / 2;
        this->menu_quit_button->m_y = this->application->getHeightF() / 2 + 30;

        this->menu_play_button->setColor(this->selected_color);

        this->application->register_keyPress_callback([&](SDL_KeyboardEvent event) -> void {
           if (event.key == SDLK_UP) {
               this->menu_choice--;
               if (this->menu_choice < MenuOptions::PLAY) {
                   this->menu_choice = MenuOptions::QUIT;
               }
           } else if (event.key == SDLK_DOWN) {
               this->menu_choice++;
               if (this->menu_choice > MenuOptions::QUIT) {
                   this->menu_choice = MenuOptions::PLAY;
               }
           }

           this->updateButtons();

           if (event.key == SDLK_RETURN) {
               switch (this->menu_choice) {
                   case MenuOptions::PLAY:
                       this->application->scene_manager->setActiveScene("game");
                       break;
                   case MenuOptions::QUIT:
                       this->application->stop();
                       break;    
               }
           }
        });
    };

    void updateButtons() {
        SDL_Color menu_play_color = this->menu_choice == MenuOptions::PLAY 
            ? this->selected_color
            : this->unselected_color;
        SDL_Color menu_settings_color = this->menu_choice == MenuOptions::SETTINGS
            ? this->selected_color
            : this->unselected_color;
        SDL_Color menu_quit_color = this->menu_choice == MenuOptions::QUIT
            ? this->selected_color 
            : this->unselected_color;

        this->menu_play_button->setColor(menu_play_color);
        this->menu_settings_button->setColor(menu_settings_color);
        this->menu_quit_button->setColor(menu_quit_color);
    }
};