#pragma once

#include <SDL3/SDL.h>
#include <optional>


class Application;

class WorldObject {
  protected:
    Application* m_application;

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

    void setX(float x);
    void setY(float x);
    void setRotation(float rotation);
    void setWidth(float width);
    void setHeight(float height);
};