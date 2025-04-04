#pragma once

#include <iostream>
#include <map>
#include <string>
#include <SDL3/SDL.h>
// #include "scene.h"

class Scene;

class SceneManager {
   private:
       std::map<std::string, Scene*> scenes_by_id;
       std::string active_scene = "";
       SDL_Renderer* m_renderer = nullptr;

   public:
       SceneManager(SDL_Window* window);
       ~SceneManager();
       SDL_Renderer* getRenderer();
       void renderScene();
       void addScene(std::string key, Scene* scene);
       Scene* getActiveScene();
};