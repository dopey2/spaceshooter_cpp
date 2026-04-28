#include "scene.h"
#include <SDL3/SDL.h>

Scene::Scene() {
    this->application = Application::getInstance();
}

Scene::Scene(const std::string &key) {
    this->application = Application::getInstance();
    application->scene_manager->addScene(key, this);
}

Scene::~Scene() {
    for(WorldObject* object: this->objects) {
        delete object;
    }
    this->objects.clear();
}

void Scene::addObject(WorldObject* const object) {
    this->objects.push_back(object);

    // post-construction hook, see WorldObject::addObject() for more details
    object->load(this->application->getRenderer());
}

void Scene::removeObject(WorldObject* const object) {
    size_t i = 0;
    for (auto iterator = this->objects.begin(); iterator != this->objects.end(); iterator++, i++) {
        if (objects.at(i) == object) {
            objects.erase(iterator);
            return;
        }
    }
}

void Scene::callOnUpdateCallback(const Uint64 delta) {
    this->onUpdate(delta);
    for(WorldObject* object: this->objects) {
        object->callUpdateCallback(delta);
    }
}

void Scene::renderAllObjects(SDL_Renderer* const renderer) {
    SDL_RenderClear(renderer);

    for(WorldObject* object: this->objects) {
        object->callRender(renderer, 0, 0);
    }

    SDL_RenderPresent(renderer);
}


/** Base class, no implementation, leave empty */
void Scene::onUpdate(Uint64) {}
/** Base class, no implementation, leave empty */
void Scene::onActive() {}