#include "../engine/application.h"
#include "../engine/keyboard.h"
#include "../engine/sprite.h"

#define MAX_VELOCITY 5
#define VELOCITY_STEP 0.1
#define VELOCITY_FRICTION 0.1

class Spaceship : public Sprite {
private:
    float x_velocity = 0;

public:
    Spaceship() : Sprite("../assets/img/spaceship.bmp") {
        this->setX(this->m_application->getWidth() / 2 - 48);
        this->setY(this->m_application->getHeight() - 48);

        this->m_application->register_update_callback([=](Uint64 _) -> void { this->onUpdate(); });
    }

    void onUpdate() {
        if (Keyboard::isKeyDown(SDLK_LEFT)) {
            if (this->x_velocity > -MAX_VELOCITY) {
                this->x_velocity -= VELOCITY_STEP;
            }
        } else if (Keyboard::isKeyDown(SDLK_RIGHT)) {
            if (this->x_velocity < MAX_VELOCITY) {
                this->x_velocity += VELOCITY_STEP;
            }
        } else if (!Keyboard::isKeyDown(SDLK_LEFT) && !Keyboard::isKeyDown(SDLK_RIGHT)) {
            if (abs(x_velocity) < VELOCITY_FRICTION) {
                this->x_velocity = 0;
            }
            if (this->x_velocity > 0) {
                this->x_velocity -= VELOCITY_FRICTION;
            } else if (this->x_velocity < 0) {
                this->x_velocity += VELOCITY_FRICTION;
            }
        }
    
        std::cout << x_velocity << std::endl;
        if (this->x_velocity != 0) {
            this->setX(this->x + this->x_velocity);
        }
    }
};
