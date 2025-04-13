#include "world_object.h"
#include <SDL3/SDL.h>
#include "application.h"

WorldObject::WorldObject() {
    this->m_application = Application::getInstance();

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


WorldObject::~WorldObject() {
    for(WorldObject* object: this->children) {
        delete object;
    }
}

void WorldObject::addObject(WorldObject* object) {
    this->children.push_back(object);
}

void WorldObject::removeObject(WorldObject* object) {
    int i = 0;
    for (auto iterator = this->children.begin(); iterator != this->children.end(); iterator++, i++) {
        if (children.at(i) == object) {
            children.erase(iterator);
            return;
        }
    }
}

void WorldObject::load(SDL_Renderer *renderer) {}

static void renderChildren(WorldObject* object, SDL_Renderer *renderer, float parent_x, float parent_y) {
    for (WorldObject* child : object->children) {
        child->render(renderer, * object->m_x + parent_x, *object->m_y + parent_y);
        renderChildren(child, renderer, parent_x, parent_y);
    }
}

void WorldObject::callRender(SDL_Renderer *renderer, float parent_x, float parent_y) {
    this->render(renderer, parent_x, parent_y);
    for(WorldObject* object : this->children) {
        object->render(renderer, *this->m_x + parent_x, *this->m_y + parent_y);
        if (object->children.size() > 0) {
            renderChildren(object, renderer, parent_x, parent_y);
        }
    }
}

void WorldObject::callOnUpdateCallbackChildren(WorldObject* object, Uint64 delta) {
    for (WorldObject* child : object->children) {
        child->onUpdate(delta);
        callOnUpdateCallbackChildren(child, delta);
    }
}

void WorldObject::callUpdateCallback(Uint64 delta) {
    this->onUpdate(delta);
    for (WorldObject *object: this->children) {
        object->onUpdate(delta);
        if (object->children.size() > 0) {
            callOnUpdateCallbackChildren(object, delta);
        }
    }
}

void WorldObject::render(SDL_Renderer *renderer, float parent_x, float parent_y) {}
void WorldObject::onUpdate(Uint64 delta) {}