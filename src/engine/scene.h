#pragma once

#include <vector>
#include <string>
#include <SDL3/SDL.h>
#include "world_object.h"
#include "application.h"

class SceneManager;

class Scene {
friend class SceneManager;
private:
    void callOnUpdateCallback(Uint64 delta);
    void renderAllObjects(SDL_Renderer* m_renderer);
protected:
    std::vector<WorldObject*> objects;
    Application* application;
    // callback to be override
    virtual void onUpdate(Uint64 delta);
    virtual void onActive();
public:
    Scene();
    Scene(std::string key);
    ~Scene();
    void addObject(WorldObject* object);
    void removeObject(WorldObject* object);
};
