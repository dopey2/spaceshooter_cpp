#include "cstdlib"
#include "../engine/sprite.h"
#include "../engine/application.h"

#define COLLISION_MARGIN 4

class Asteroid : public Sprite {
public:
    Asteroid() : Sprite("../assets/img/asteroid.bmp") {
        this->setWidth(50);
        this->setHeight(50);
        int random_x_position = rand() % (this->m_application->getWidth() - 50);
        this->setX(random_x_position);
        this->setY(-50);
    }

    void updateAsteroidPosition() {
        this->setY(*this->m_y + 1);
    }

    bool isOutOfScreen() {
        return *this->m_y > m_application->getHeight();
    }

    bool isHittingTheSpaceship(Spaceship* spaceship) {
        if (
            *spaceship->m_x + *spaceship->m_width - COLLISION_MARGIN >= *this->m_x &&
            *spaceship->m_x + COLLISION_MARGIN <= *this->m_x + *this->m_width &&
            *spaceship->m_y <= *this->m_y + *this->m_height &&
            *spaceship->m_y + *spaceship->m_height >= *this->m_y
            ) {
            return true;
        }

        return false;
    }
};