#include "world_object.h"
#include <SDL3/SDL.h>
#include "application.h"

WorldObject::WorldObject() { this->m_application = Application::getInstance(); }

WorldObject::~WorldObject() {}

void WorldObject::load(SDL_Renderer *renderer) {}
void WorldObject::unload() {}
void WorldObject::render(SDL_Renderer *renderer) {};
void WorldObject::onUpdate(Uint64 delta) {};

void WorldObject::setX(float x) {
    if (this->m_x == nullptr) {
        this->m_x = (float *) malloc(sizeof(float));
    }
    *this->m_x = x;
}

void WorldObject::setY(float y) {
    if (this->m_y == nullptr) {
        this->m_y = (float *) malloc(sizeof(float));
    }
    *this->m_y = y;
}

void WorldObject::setRotation(float rotation) {
    if (this->m_rotation == nullptr) {
        this->m_rotation = (float *) malloc(sizeof(float));
    }
    *this->m_rotation = rotation;
}

void WorldObject::setWidth(float width) {
    if (this->m_width == nullptr) {
        this->m_width = (float *) malloc(sizeof(float));
    }
    *this->m_width = width;
}

void WorldObject::setHeight(float height) {
    if (this->m_height == nullptr) {
        this->m_height = (float *) malloc(sizeof(float));
    }
    *this->m_height = height;
}