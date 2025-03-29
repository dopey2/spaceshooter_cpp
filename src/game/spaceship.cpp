#include "../engine/sprite.h"
#include "../engine/application.h"

class Spaceship : public Sprite {
    public:
      Spaceship() : Sprite("../assets/img/spaceship.bmp") {
        this->m_application->scene->addObject(this);

        this->setX(this->m_application->getWidth() / 2 - 48);
        this->setY(this->m_application->getHeight() - 48);

        this->m_application->register_keyPress_callback([=](SDL_KeyboardEvent event) -> void {
          if (event.key == SDLK_LEFT) {
           this->setX(this->x - 1);
          } else if (event.key == SDLK_RIGHT) {
            this->setX(this->x + 1);
          }
        });
     }
};