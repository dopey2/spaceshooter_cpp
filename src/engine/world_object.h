#pragma once

#include <SDL3/SDL.h>


class Application;

class WorldObject {
  protected:
    Application* m_application;
    float m_x;
    float m_y;
    float m_rotation;
    float m_width;
    float m_height;

  public:
    const float &x = m_x;
    const float &y = m_y;
    const float &rotation = m_rotation;
    const float &width = m_width;
    const float &height = m_height;

    WorldObject();
    virtual void load(SDL_Renderer *renderer);
    virtual void unload();
    virtual void render(SDL_Renderer *renderer);

    void setX(float x);
    void setY(float x);
    void setPosition(float x, float y);
    void setRotation(float rotation);
    void setWidth(float width);
    void setHeight(float height);
};