#include "../engine/application.h"
#include "../engine/keyboard.h"
#include "../engine/scene.h"
#include "../engine/text.h"
#include "../engine/sprite_animated.h"

#define MENU_PLAY 0
#define MENU_SETTINGS 1
#define MENU_QUIT 2

class MenuScene : public Scene {
private:
    Text* menu__play_button = nullptr;
    Text* menu__settings_button = nullptr;
    Text* menu__quit_button = nullptr;

    SDL_Color* selected_color = new SDL_Color({200, 50, 50, SDL_ALPHA_OPAQUE});
    SDL_Color* unselected_color = new SDL_Color({255, 255, 255, SDL_ALPHA_OPAQUE});

    int8_t menu_choice = MENU_PLAY;

public:
    MenuScene() {
        this->menu__play_button = new Text("../assets/font/Arial.ttf", "Play", 24);
        this->menu__settings_button = new Text("../assets/font/Arial.ttf", "Settings", 24);
        this->menu__quit_button = new Text("../assets/font/Arial.ttf", "Quit", 24);

        this->addObject(menu__play_button);
        this->addObject(menu__settings_button);
        this->addObject(menu__quit_button);

        this->menu__play_button->setX((this->application->getWidth() - *menu__play_button->m_width) / 2);
        this->menu__settings_button->setX((this->application->getWidth() - *menu__settings_button->m_width) / 2);
        this->menu__quit_button->setX((this->application->getWidth() - *menu__quit_button->m_width) / 2);

        this->menu__play_button->setY(this->application->getHeight() / 2 - 30);
        this->menu__settings_button->setY(this->application->getHeight() / 2);
        this->menu__quit_button->setY(this->application->getHeight() / 2 + 30);

        this->menu__play_button->setColor(this->selected_color);

        this->application->register_keyPress_callback([&](SDL_KeyboardEvent event) -> void {
           if (event.key == SDLK_UP) {
               this->menu_choice--;
               if (this->menu_choice < MENU_PLAY) {
                   this->menu_choice = MENU_QUIT;
               }
           } else if (event.key == SDLK_DOWN) {
               this->menu_choice++;
               if (this->menu_choice > MENU_QUIT) {
                   this->menu_choice = MENU_PLAY;
               }
           }

           this->updateButtons();

           if (event.key == SDLK_RETURN) {
               switch (this->menu_choice) {
                   case MENU_PLAY:
                       this->application->scene_manager->setActiveScene("game");
                       break;
                   case MENU_QUIT:
                       this->application->stop();
                       break;
               }
           }
        });
    };

    void updateButtons() {
        SDL_Color* menu_play_color = this->menu_choice == MENU_PLAY ? this->selected_color : this->unselected_color;
        SDL_Color* menu_settings_color = this->menu_choice == MENU_SETTINGS ? this->selected_color : this->unselected_color;
        SDL_Color* menu_quit_color = this->menu_choice == MENU_QUIT ? this->selected_color : this->unselected_color;

        this->menu__play_button->setColor(menu_play_color);
        this->menu__settings_button->setColor(menu_settings_color);
        this->menu__quit_button->setColor(menu_quit_color);
    }
};