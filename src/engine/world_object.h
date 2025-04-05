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
//     const float x = &m_x.value_or(0);
//     const float y = &m_y.value_or(0);
//     const float width = &m_width.value_or(0);
//     const float height = &m_height.value_or(0);
//     const float rotation = &m_rotation.value_or(0);


    WorldObject();
    virtual ~WorldObject();

    void init_x();
    void init_y();
    void init_width();
    void init_height();
    void init_rotation();

    virtual void load(SDL_Renderer *renderer);
    virtual void unload();
    virtual void render(SDL_Renderer *renderer);

    void setX(float x);
    void setY(float x);
    void setRotation(float rotation);
    void setWidth(float width);
    void setHeight(float height);
};