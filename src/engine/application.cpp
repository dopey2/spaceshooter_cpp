#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include <iostream>
#include <vector>
#include "scene.cpp"

class Application {

  private:
    static Application* m_instance;
    const char *m_title = nullptr;
    uint16_t m_width = 0;
    uint16_t m_height = 0;
    bool m_is_running = false;

    std::vector<void(*)()> m_callbacks_update;
    std::vector<std::function<void(SDL_KeyboardEvent)>> m_callbacks_keyPress;

    Application(const char* title, uint16_t width, uint16_t height) {
      this->m_title = title;
      this->m_width = width;
      this->m_height = height;

      this->initWindow();
      this->initSDL();

      this->scene = new Scene(this->_window);
    }

    ~Application() {
        SDL_DestroyWindow(_window);
    }


  public:
    SDL_Window* _window = nullptr;
    Scene* scene = nullptr;

    uint16_t getWidth() {
      return this->m_width;
    }

    uint16_t getHeight() {
      return this->m_height;
    }

  private:
    void initSDL() {
      if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
      }
    }

    void initWindow() {
      this->_window = SDL_CreateWindow(this->m_title, this->m_width, this-> m_height, SDL_WINDOW_OPENGL);
      if (this->_window == NULL) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
      }
    }


  public:
  // for the singleton pattern: disable the public constructor
  Application(Application const&) = delete;
  // for the singleton pattern: disable the assignment operator
  void operator=(Application const&) = delete;

  static Application* getInstance(const char* title, uint16_t width, uint16_t height) {
    if (Application::m_instance == nullptr) {
      Application::m_instance = new Application(title, width, height);
    }

    return Application::m_instance;
  }

  void run() {
    this->m_is_running = true;

    while (this->m_is_running) {
      SDL_Event event;

      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
          this->m_is_running = false;
          std::cout << "Quitting..." << std::endl;
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
          for (auto callback : this->m_callbacks_keyPress) {
            callback(event.key);
          }
        }
      }

      for (auto callback : this->m_callbacks_update) {
        callback();
      }

      this->scene->renderAllObjects();
    }

    SDL_DestroyWindow(this->_window);
  }

  void stop() {
    this->m_is_running = false;
  }

  void register_update_callback(void(*update_callback)()) {
    this->m_callbacks_update.push_back(update_callback);
  }

  void register_keyPress_callback(std::function<void(SDL_KeyboardEvent event)> keyPress_callback) {
    this->m_callbacks_keyPress.push_back(keyPress_callback);
  }
};

Application* Application::m_instance = nullptr;

