#pragma once

#include <SDL3/SDL.h>
#include <optional>

class Application;
class Scene;

class WorldObject {
friend class Scene;
protected:
    Application* m_application;
    virtual void onUpdate(Uint64 delta);

public:
    float* m_x = nullptr;
    float* m_y = nullptr;
    float* m_width = nullptr;
    float* m_height = nullptr;
    float* m_rotation = nullptr;

    WorldObject();
    virtual ~WorldObject();

    virtual void load(SDL_Renderer *renderer);
    virtual void unload();
    virtual void render(SDL_Renderer *renderer);
};