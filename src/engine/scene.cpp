#include <SDL3/SDL.h>
#include <iostream>
#include "scene.h"

Scene::Scene(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    this->m_renderer = renderer;
}

Scene::~Scene() {
    for(WorldObject* object: this->objects) {
        delete object;
    }
}


void Scene::addObject(WorldObject* object) {
    this->objects.push_back(object);
}

void Scene::updateAllObjects() {
    for(WorldObject* object: this->objects) {
        object->render(this->m_renderer);
    }
}

void Scene::renderAllObjects() {
    SDL_RenderClear(this->m_renderer);

    for(WorldObject* object: this->objects) {
        object->render(this->m_renderer);
    }

    SDL_RenderPresent(this->m_renderer);
}