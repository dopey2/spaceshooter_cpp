#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include <iostream>
#include <vector>
#include "scene.h"
#include "scene_manager.h"

class Application {

  private:
    static Application* m_instance;
    const char *m_title = nullptr;
    int m_width = 0;
    int m_height = 0;
    bool m_is_running = false;

    std::vector<std::function<void(Uint64 delta)>> m_callbacks_update;
    std::vector<std::function<void(SDL_KeyboardEvent)>> m_callbacks_keyPress;

    Application(const char* title, int width, int height);


  public:
    SDL_Window* _window = nullptr;
    SceneManager* scene_manager = nullptr;

    int getWidth();
    int getHeight();
    float getWidthF();
    float getHeightF();

  private:
    void initSDL();
    void initWindow();


  public:
  // for the singleton pattern: disable the public constructor
  Application(Application const&) = delete;
  // for the singleton pattern: disable the assignment operator
  void operator=(Application const&) = delete;
  ~Application();
  static Application* createInstance(const char* title, int width, int height);
  static Application* getInstance();
  void run();
  void stop();
  void register_update_callback(std::function<void(Uint64 delta)>);
  void register_keyPress_callback(std::function<void(SDL_KeyboardEvent event)> keyPress_callback);
};
