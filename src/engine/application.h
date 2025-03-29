#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include <iostream>
#include <vector>
#include "scene.h"

class Application {

  private:
    static Application* m_instance;
    const char *m_title = nullptr;
    uint16_t m_width = 0;
    uint16_t m_height = 0;
    bool m_is_running = false;

    std::vector<void(*)()> m_callbacks_update;
    std::vector<std::function<void(SDL_KeyboardEvent)>> m_callbacks_keyPress;

    Application(const char* title, uint16_t width, uint16_t height);
    ~Application();


  public:
    SDL_Window* _window = nullptr;
    Scene* scene = nullptr;

    uint16_t getWidth();
    uint16_t getHeight();

  private:
    void initSDL();
    void initWindow();


  public:
  // for the singleton pattern: disable the public constructor
  Application(Application const&) = delete;
  // for the singleton pattern: disable the assignment operator
  void operator=(Application const&) = delete;
  static Application* createInstance(const char* title, uint16_t width, uint16_t height);
  static Application* getInstance();
  void run();
  void stop();
  void register_update_callback(void(*update_callback)());
  void register_keyPress_callback(std::function<void(SDL_KeyboardEvent event)> keyPress_callback);
};
