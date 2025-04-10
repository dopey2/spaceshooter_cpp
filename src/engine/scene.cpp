#include <SDL3/SDL.h>
#include "scene.h"

Scene::Scene() {
    this->application = Application::getInstance();
}

Scene::Scene(std::string key) {
    this->application = Application::getInstance();
    application->scene_manager->addScene(key, this);
}

Scene::~Scene() {
    for(WorldObject* object: this->objects) {
        delete object;
    }
}

void Scene::onUpdate(Uint64 delta) {}

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
        object->onUpdate(delta);
    }
}

void Scene::renderAllObjects(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);

    for(WorldObject* object: this->objects) {
        object->render(renderer, 0, 0);
    }

    SDL_RenderPresent(renderer);
}