#pragma once

#include <SDL3/SDL.h>

class WorldObject {

    protected:
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

      WorldObject() {
         this->m_x = 0;
         this->m_y = 0;
         this->m_rotation = 0;
         this->m_width = 0;
         this->m_height = 0;
      }

      virtual void load(SDL_Renderer *renderer) {}
      virtual void unload() {}
      virtual void render(SDL_Renderer *renderer){};

    void setX(float x) { this->m_x = x; }
    void setY(float x) { this->m_x = x; }
    void setPosition(float x, float y) { this->m_x = x; this->m_y = y; }
    void setRotation(float rotation) { this->m_rotation = rotation; }
    void setWidth(float width) { this->m_width = width; }
    void setHeight(float height) { this->m_height = height; }
};