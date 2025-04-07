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

    // callback to be override
    virtual void onUpdate(Uint64 delta);

    void addObject(WorldObject* object);
    void removeObject(WorldObject* object);


    // make private and friend of scene manager
    void callOnUpdateCallback(Uint64 delta);
    void renderAllObjects(SDL_Renderer* m_renderer);
};
