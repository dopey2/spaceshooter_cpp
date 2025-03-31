#include "../engine/sprite.h"
#include "../engine/application.h"
#include "../engine/keyboard.h"

class Spaceship : public Sprite {
  private:
    float x_velocity = 0;

    public:
      Spaceship() : Sprite("../assets/img/spaceship.bmp") {
        this->setX(this->m_application->getWidth() / 2 - 48);
        this->setY(this->m_application->getHeight() - 48);

        this->m_application->register_update_callback([=](Uint64 _) -> void {
          this->onUpdate();
        });
     }

     void onUpdate() {

        if (Keyboard::isKeyDown(SDLK_LEFT)) {
          if (this->x_velocity > -0.05) {
            this->x_velocity -= 0.0001;
          }
        } else if (Keyboard::isKeyDown(SDLK_RIGHT)) {
          if (this->x_velocity < 0.05) {
            this->x_velocity += 0.0001;
          }
        }

        if (!Keyboard::isKeyDown(SDLK_LEFT) && !Keyboard::isKeyDown(SDLK_RIGHT)) {
          if (this->x_velocity > 0) {
            this->x_velocity -= 0.0001;
          }
          if (this->x_velocity < 0) {
            this->x_velocity += 0.0001;
          }
        }


        std::cout << x_velocity << std::endl;
        this->setX(this->x + this->x_velocity);
     }
};