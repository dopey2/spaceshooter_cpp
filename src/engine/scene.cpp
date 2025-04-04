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

void Scene::addObject(WorldObject* object) {
    this->objects.push_back(object);
}

void Scene::renderAllObjects(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);

    for(WorldObject* object: this->objects) {
        object->render(renderer);
    }

    SDL_RenderPresent(renderer);
}