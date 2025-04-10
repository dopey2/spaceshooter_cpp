#include "cstdlib"
#include "../engine/sprite.h"
#include "../engine/application.h"
#include "spaceship.cpp"

#define COLLISION_MARGIN 4

class Asteroid : public Sprite {
public:
    Asteroid() : Sprite("../assets/img/asteroid.bmp") {
        *this->m_width = 50;
        *this->m_height = 50;
        int random_x_position = rand() % (this->m_application->getWidth() - 50);
        *this->m_x = random_x_position;
        *this->m_y = -50;
    }

    void updateAsteroidPosition() {
        *this->m_y = *this->m_y + 1;
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