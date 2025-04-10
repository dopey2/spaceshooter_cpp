#include "application.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <functional>
#include <iostream>

#include "assets_loader.h"
#include "keyboard.h"

#define TARGET_FPS 60
#define INTERVAL_BETWEEN_DRAWS_CALL (1000 / TARGET_FPS)

Application::Application(const char *title, uint16_t width, uint16_t height) {
    this->m_title = title;
    this->m_width = width;
    this->m_height = height;
    this->initWindow();
    this->initSDL();
    this->scene_manager = new SceneManager(this->_window);
}

Application::~Application() {
    m_instance = nullptr;
    SDL_DestroyWindow(_window);
    delete this->scene_manager;
    this->scene_manager = nullptr;
    AssetsLoaders::clearTexturesFromCache();
}

Application *Application::createInstance(const char *title, uint16_t width, uint16_t height) {
    if (m_instance == nullptr) {
        m_instance = new Application(title, width, height);
    }

    return m_instance;
}

Application *Application::getInstance() { return m_instance; }

void Application::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }

    if (!TTF_Init()) {
        std::cerr << "SDL could not initialize SDL_ttf ! SDL_Error: " << SDL_GetError() << std::endl;
    }
}

void Application::initWindow() {
    this->_window = SDL_CreateWindow(this->m_title, this->m_width, this->m_height, SDL_WINDOW_OPENGL);
    if (this->_window == NULL) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }
}

uint16_t Application::getWidth() { return this->m_width; }

uint16_t Application::getHeight() { return this->m_height; }

void Application::run() {
    this->m_is_running = true;

    while (this->m_is_running) {
        SDL_Event event;

        float start_work_delta = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                this->m_is_running = false;
                std::cout << "Quitting..." << std::endl;
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
                Keyboard::onKeyDown(event.key.key);
                for (auto callback: this->m_callbacks_keyPress) {
                    callback(event.key);
                }
            } else if (event.type == SDL_EVENT_KEY_UP) {
                Keyboard::onKeyUp(event.key.key);
            }
        }

        if (this->m_is_running) {
            // scene scoped on update
            this->scene_manager->callOnUpdateCallback(SDL_GetTicks());
            // global on update
            for (auto callback: this->m_callbacks_update) {
                callback(SDL_GetTicks());
            }

            this->scene_manager->renderScene();
            float work_duration = SDL_GetTicks() - start_work_delta;
            if (work_duration > INTERVAL_BETWEEN_DRAWS_CALL) {
                work_duration = INTERVAL_BETWEEN_DRAWS_CALL;
            }
            SDL_Delay(INTERVAL_BETWEEN_DRAWS_CALL - work_duration);
        }
    }

    Application::~Application();
}

void Application::stop() { this->m_is_running = false; }

void Application::register_update_callback(std::function<void(Uint64 delta)> update_callback) {
    this->m_callbacks_update.push_back(update_callback);
}

void Application::register_keyPress_callback(std::function<void(SDL_KeyboardEvent event)> keyPress_callback) {
    this->m_callbacks_keyPress.push_back(keyPress_callback);
}

Application *Application::Application::m_instance = nullptr;
