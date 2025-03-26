#pragma once

class WorldObject {
    public:
      float* x;
      float* y;
      float* rotation;
      float* width;
      float* height;

      WorldObject() {
         float _x = 0, _y = 0, _rotation = 0, _width = 0, _height = 0;

         this->x = &_x;
         this->y = &_y;
         this->rotation = &_rotation;
         this->width = &_width;
         this->height = &_height;
      }

      virtual void load(SDL_Renderer *renderer) {}
      virtual void unload() {}
      virtual void render(SDL_Renderer *renderer){};
};