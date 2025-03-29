#pragma once

#include <iostream>
#include <SDL3/SDL.h>
#include <vector>
#include "world_object.h"


class Scene {
private:
    std::vector<WorldObject*> objects;
    SDL_Renderer* m_renderer;

public:
    Scene(SDL_Window* window);
    void addObject(WorldObject* object);
    void renderAllObjects();
};
