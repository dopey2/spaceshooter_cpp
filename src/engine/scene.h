#pragma once

#include <vector>
#include <string>
#include <SDL3/SDL.h>
#include "world_object.h"
#include "application.h"

class Scene {
protected:
    std::vector<WorldObject*> objects;
    Application* application;

public:
    Scene();
    Scene(std::string key);
    ~Scene();
    void addObject(WorldObject* object);
    void renderAllObjects(SDL_Renderer* m_renderer);
};
