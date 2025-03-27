#pragma once

#include <iostream>
#include <vector>
#include <SDL3/SDL.h>


class AppUpdateObserver {
public:
  AppUpdateObserver(){}
  virtual ~AppUpdateObserver(){}
  friend class Application;
  virtual void application_interface_onUpdate() {};
};

class AppLoadObserver {
public:
  AppLoadObserver(){}
  virtual ~AppLoadObserver(){}
  friend class Application;
  virtual void application_interface_onLoad() {
    std::cout << "Application loading..." << std::endl;
  };
  virtual void application_interface_unonLoad() {

  };
};

class Application {

  private:
    static Application* m_instance;
    const char *m_title = nullptr;
    uint16_t m_width = 0;
    uint16_t m_height = 0;
    bool m_is_running = false;

    std::vector<AppUpdateObserver*> m_update_observers;
    std::vector<AppLoadObserver*> m_onload_observers;

    Application(const char* title, uint16_t width, uint16_t height) {
      this->m_title = title;
      this->m_width = width;
      this->m_height = height;

      this->initWindow();
      this->initSDL();
    }

    ~Application() {
        SDL_DestroyWindow(_window);
    }


  public:
    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;

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
    this->notify_onloadObservers();

    this->m_is_running = true;

    while (this->m_is_running) {
      SDL_Event event;

      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
          this->m_is_running = false;
          std::cout << "Quitting..." << std::endl;
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
          // this->callback_keyboard_down(event.key);
        }
      }

      this->notify_updateObservers();
    }

    this->notify_unloadObservers();
    SDL_DestroyWindow(this->_window);
  }

  void stop() {
    this->m_is_running = false;
  }

  void add_updateObserver(AppUpdateObserver* observer) {
    this->m_update_observers.push_back(observer);
  }

  void add_onloadObserver(AppLoadObserver* observer) {
    this->m_onload_observers.push_back(observer);
  }

  void notify_updateObservers() {
    for (AppUpdateObserver* observer : this->m_update_observers) {
      observer->application_interface_onUpdate();
    }
  }

  void notify_onloadObservers() {
    for (AppLoadObserver* observer : this->m_onload_observers) {
      observer->application_interface_onLoad();
    }
  }

  void notify_unloadObservers() {
    for (AppLoadObserver* observer : this->m_onload_observers) {
      observer->application_interface_unonLoad();
    }
  }
};

Application* Application::m_instance = nullptr;

