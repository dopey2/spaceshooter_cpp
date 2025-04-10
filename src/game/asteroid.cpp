#pragma once

#include "../engine/__engine.h"
#include "spaceship_view.cpp"

#define COLLISION_MARGIN 4


class Asteroid : public View {
public:
    std::vector<Sprite*> asteroid_parts;
    bool is_destroyed = 0;
    std::vector<std::pair<float, float>> parts_velocity;


    Asteroid() {
        int random_x_position = rand() % (Application::getInstance()->getWidth() - 50);
        *this->m_width = 50;
        *this->m_height = 50;
        *this->m_x = random_x_position;
        *this->m_y = -50;

        for (int i = 1; i < 12; i++) {
            std::string part_path = "../assets/img/asteroid/variant_A/variant_A_" + std::to_string(i) + ".bmp";
            Sprite* part = new Sprite(part_path);
            *part->m_width = 50;
            *part->m_height = 50;
            this->asteroid_parts.push_back(part);
            this->addObject(part);
        }
    }

    void updateVelocity(float &velocity) {
        if (abs(velocity) < 0.01) {
            velocity = 0;
        }

        velocity *= 0.985;
        return;

        if (velocity > 0) {
            velocity -= 0.02;
        }

        if (velocity < 0) {
            velocity += 0.02;
        }
    }

    void updateAsteroidPosition() {
        *this->m_y = *this->m_y + 1;

        if (this->is_destroyed) {
            for (int i = 0; i < 11; i++) {
                *this->asteroid_parts[i]->m_x += this->parts_velocity[i].first;
                *this->asteroid_parts[i]->m_y += this->parts_velocity[i].second;
                this->updateVelocity(this->parts_velocity[i].first);
                this->updateVelocity(this->parts_velocity[i].second);
            }
        }
    }

    void destroyAsteroid() {
        if (this->is_destroyed) {
            return;
        }

        this->is_destroyed = true;

        for (int i = 0; i < 11; i++) {
            parts_velocity.push_back({(rand() % 6) - 3, (rand() % 6) - 3});
        }
    }

    bool isOutOfScreen() {
        return *this->m_y > Application::getInstance()->getHeight() * 2;
    }

    bool isColliding(WorldObject* object) {
        if (this->is_destroyed) {
            return false;
        }

        if (
            *object->m_x + *object->m_width - COLLISION_MARGIN >= *this->m_x &&
            *object->m_x + COLLISION_MARGIN <= *this->m_x + *this->m_width &&
            *object->m_y <= *this->m_y + *this->m_height &&
            *object->m_y + *object->m_height >= *this->m_y
            ) {
            return true;
            }

        return false;
    }
};