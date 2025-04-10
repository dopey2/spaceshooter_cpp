#include <stdlib.h>
#include "view.h"

View::View() {
    this->m_x = (float*) malloc(sizeof(float));
    *this->m_x = 0;

    this->m_y = (float*) malloc(sizeof(float));
    *this->m_y = 0;

    this->m_width = (float*) malloc(sizeof(float));
    *this->m_width = 0;

    this->m_height = (float*) malloc(sizeof(float));
    *this->m_height = 0;

    this->m_rotation = (float*) malloc(sizeof(float));
    *this->m_rotation = 0;
}

View::~View() {
    for(WorldObject* object: this->children) {
        delete object;
    }
}

void View::load(SDL_Renderer* renderer) {}

void View::render(SDL_Renderer *renderer, float parent_x, float parent_y) {
    for(WorldObject* object : this->children) {
        object->render(renderer, *this->m_x + parent_x, *this->m_y + parent_y);
    }
}

void View::addObject(WorldObject* object) {
    this->children.push_back(object);
}


