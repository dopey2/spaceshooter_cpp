#include <iostream>
#include <SDL3/SDL.h>

class Application {

  private:

    uint16_t _width = 0;
    uint16_t _height = 0;
    bool isRunning = false;

  public:
    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;

    static Application* _instance;

    // For the singleton: disable constructor by reference
    Application(Application const&) = delete;
    // For the singleton: disable assignment operator
    void operator=(Application const&)  = delete;

    uint16_t getWidth() {
      return this->_width;
    }

    uint16_t getHeight() {
      return this->_height;
    }

  private:
    void(*callback_render)(Application* application, SDL_Window* window,SDL_Renderer* renderer) = nullptr;
    void(*callback_keyboard_down)(SDL_KeyboardEvent event) = nullptr;

    void initSDL() {
      if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
      }
    }

    void initWindow(const char* title, int width, int height) {
      this->_window = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL);
      if (this->_window == NULL) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
      }
    }

    void initRenderer() {
      this->_renderer = SDL_CreateRenderer(this->_window, NULL);
      if (this->_renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(this->_window);
        SDL_Quit();
      }
    }


  public:

  Application(const char* title, uint16_t width, uint16_t height) {
    this->initSDL();
    this->initWindow(title, width, height);
    this->initRenderer();
    this->_height = _height;
    this->_width = _width;
  }

  ~Application() {
    SDL_DestroyWindow(_window);
  }

  static Application* getInstance(const char* title, uint16_t width, uint16_t height) {
    if (Application::_instance == nullptr) {
      Application::_instance = new Application(title, width, height);
    }
    return Application::_instance;
  }


  void run() {
    this->isRunning = true;

    while (this->isRunning) {
      SDL_Event event;

      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
          this->isRunning = false;
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
          this->callback_keyboard_down(event.key);
        }
      }

      this->callback_render(this, this->_window, this->_renderer);
    }

    SDL_DestroyWindow(this->_window);
  }

  void stop() {
    this->isRunning = false;
  }

  void onRender(void(*callback)(Application* application, SDL_Window* window, SDL_Renderer* renderer)) {
    this->callback_render = callback;
  }

  void onKeyEventDown(void(*callback)(SDL_KeyboardEvent event)) {
    this->callback_keyboard_down = callback;
  }
};

Application* Application::_instance = nullptr;