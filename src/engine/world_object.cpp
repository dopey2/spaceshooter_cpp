#include "world_object.h"
#include <SDL3/SDL.h>
#include "application.h"

WorldObject::WorldObject() {
    this->m_application = Application::getInstance();

    this->m_x = 0;
    this->m_y = 0;
    this->m_width = 0;
    this->m_height = 0;
    this->m_rotation = 0;
}


WorldObject::~WorldObject() {
    for(WorldObject* object: this->children) {
        delete object;
    }
}

void WorldObject::addObject(WorldObject* const object) {
    this->children.push_back(object);

    // the .addObject() method being the natural lifecycle method following the constructor
    // i've called load() here, this ensure load is always called after constructor while respecting polymorphism rules for subclass
    // properties like m_width & m_height are available only after the object has been added in the tree/graph

    // Note 1:  
    //  - this is only for the first loading,
    //  - property changes like fontSize in text might require manually calling .load() again
    // Note 2:
    //  - dimension value which are != 0 must be preserved during loading phase
    //  - those are set manually by the user before adding the object in the tree/add
    object->load(this->m_application->getRenderer());
    
}

void WorldObject::removeObject(WorldObject* const object) {
    size_t i = 0;
    for (auto iterator = this->children.begin(); iterator != this->children.end(); iterator++, i++) {
        if (children.at(i) == object) {
            children.erase(iterator);
            return;
        }
    }
}

static void renderChildrenRecursively(WorldObject* const object, SDL_Renderer* const renderer, const float parent_x, const float parent_y) {
    for (WorldObject* child : object->children) {
        child->render(renderer, object->m_x + parent_x, object->m_y + parent_y);
        renderChildrenRecursively(child, renderer, object->m_x + parent_x, object->m_y + parent_y);
    }
}

void WorldObject::callRender(SDL_Renderer* const renderer, const float parent_x, const float parent_y) {
    this->render(renderer, parent_x, parent_y);
    renderChildrenRecursively(this, renderer, parent_x, parent_y);
}

void WorldObject::callOnUpdateCallbackChildren(WorldObject* const object, const Uint64 delta) {
    for (WorldObject* child : object->children) {
        child->onUpdate(delta);
        callOnUpdateCallbackChildren(child, delta);
    }
}

void WorldObject::callUpdateCallback(const Uint64 delta) {
    this->onUpdate(delta);
    for (WorldObject *object: this->children) {
        object->onUpdate(delta);
        if (object->children.size() > 0) {
            callOnUpdateCallbackChildren(object, delta);
        }
    }
}

/** Base class, no implementation, leave empty */
void WorldObject::load(SDL_Renderer*) {}
/** Base class, no implementation, leave empty */
void WorldObject::render(SDL_Renderer*, const float, const float) {}
/** Base class, no implementation, leave empty */
void WorldObject::onUpdate(Uint64) {}