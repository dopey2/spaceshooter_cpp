#pragma once

#include <iostream>
#include <SDL3/SDL.h>
#include <vector>
#include "world_object.cpp"


class Scene {
private:
    std::vector<WorldObject*> objects;
    SDL_Renderer* m_renderer;

public:
    Scene(SDL_Window* window) {
        SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

        if (renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
        }

        this->m_renderer = renderer;
    }


    void addObject(WorldObject* object) {
      this->objects.push_back(object);
    }

    void renderAllObjects() {
        SDL_RenderClear(this->m_renderer);

        for(WorldObject* object: this->objects) {
            object->render(this->m_renderer);
        }

        SDL_RenderPresent(this->m_renderer);
    }
};
