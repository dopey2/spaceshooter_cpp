#include <SDL3/SDL.h>
#include "world_object.h"
#include "application.h"

WorldObject::WorldObject() {
    this->m_application = Application::getInstance();
    this->m_x = 0;
    this->m_y = 0;
    this->m_rotation = 0;
    this->m_width = -1;
    this->m_height = -1;
}

WorldObject::~WorldObject() {}

void WorldObject::load(SDL_Renderer *renderer) {}
void WorldObject::unload() {}
void WorldObject::render(SDL_Renderer *renderer){};

void WorldObject::setX(float x) {
    this->m_x = x;
}

void WorldObject::setY(float y) {
    this->m_y = y;
}

void WorldObject::setRotation(float rotation) {
    this->m_rotation = rotation;
}

void WorldObject::setWidth(float width) {
    this->m_width = width;
}

void WorldObject::setHeight(float height) {
    this->m_height = height;
}