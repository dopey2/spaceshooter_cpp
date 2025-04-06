#include "cstdlib"
#include "../engine/sprite.h"
#include "../engine/application.h"

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
};