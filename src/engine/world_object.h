#pragma once

#include <SDL3/SDL.h>
#include <optional>
#include <vector>
#include <string>

class Application;
class Scene;

class WorldObject {
friend class Scene;

private:
    void callOnUpdateCallbackChildren(WorldObject* object, Uint64 delta);
    void callUpdateCallback(Uint64 delta);
    void callRender(SDL_Renderer *renderer, float parent_x, float parent_y);

protected:
    Application* m_application;
    virtual void onUpdate(Uint64 delta);

public:
    std::string name = "";

    WorldObject* parent = nullptr;
    std::vector<WorldObject*> children;

    float* m_x = nullptr;
    float* m_y = nullptr;
    float* m_width = nullptr;
    float* m_height = nullptr;
    float* m_rotation = nullptr;

    WorldObject();
    virtual ~WorldObject();
    void addObject(WorldObject* object);
    void removeObject(WorldObject* object);
    virtual void load(SDL_Renderer *renderer);
    virtual void render(SDL_Renderer *renderer, float parent_x, float parent_y);
};