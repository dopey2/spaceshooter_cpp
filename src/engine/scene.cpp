#include "scene.h"
#include <SDL3/SDL.h>

Scene::Scene() {
    this->application = Application::getInstance();
}

Scene::Scene(std::string key) {
    this->application = Application::getInstance();
    application->scene_manager->addScene(key, this);
}

Scene::~Scene() {
    this->objects.clear();
    // for(WorldObject* object: this->objects) {
    //     delete object;
    // }
}

void Scene::onUpdate(Uint64 delta) {}
void Scene::onActive() {}

void Scene::addObject(WorldObject* object) {
    this->objects.push_back(object);
}

void Scene::removeObject(WorldObject* object) {
    int i = 0;
    for (auto iterator = this->objects.begin(); iterator != this->objects.end(); iterator++, i++) {
        if (objects.at(i) == object) {
            objects.erase(iterator);
            return;
        }
    }
}

void Scene::callOnUpdateCallback(Uint64 delta) {
    this->onUpdate(delta);
    for(WorldObject* object: this->objects) {
        object->callUpdateCallback(delta);
    }
}

void Scene::renderAllObjects(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);

    for(WorldObject* object: this->objects) {
        object->callRender(renderer, 0, 0);
    }

    SDL_RenderPresent(renderer);
}