#include "application.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <functional>
#include <iostream>

#include "assets_loader.h"
#include "mouse_keyboard.h"
#include "logger.h"

Application::Application(const char *title, const int width, const int height, const int targetFps) {
    this->m_title = title;
    this->m_width = width;
    this->m_height = height;
    this->m_interval_between_drawcall = 1000.0f / static_cast<float>(targetFps); 
    this->initWindow();
    this->initSDL();
    this->scene_manager = new SceneManager(this->_window);
}

Application::~Application() {
    m_instance = nullptr;
    SDL_DestroyWindow(this->_window);

    delete this->scene_manager;
    this->scene_manager = nullptr;
    
    AssetsLoaders::clearTexturesFromCache();
}

Application *Application::createInstance(const char *title, const int width, const int height, const int targetFps) {
    if (m_instance == nullptr) {
        m_instance = new Application(title, width, height, targetFps);
    }

    return m_instance;
}

Application *Application::getInstance() { return m_instance; }

void Application::initSDL() {

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        Logger::error("Application: SDL could not initialize !");
        Logger::error("SDL_Error: " + static_cast<std::string>(SDL_GetError()));
    }

    if (!TTF_Init()) {
        Logger::error("Application: SDL could not initialize SDL_TTF!");
        Logger::error("SDL_Error: " + static_cast<std::string>(SDL_GetError()));
    }
}

void Application::initWindow() {
    this->_window = SDL_CreateWindow(this->m_title, this->m_width, this->m_height, SDL_WINDOW_OPENGL);
    if (this->_window == nullptr) {
        Logger::error("Application: Window could not be created !");
        Logger::error("SDL_Error: " + static_cast<std::string>(SDL_GetError()));
    }
}

int Application::getWidth() { return this->m_width; }

int Application::getHeight() { return this->m_height; }

float Application::getWidthF() { return static_cast<float>(this->m_width); }

float Application::getHeightF() { return static_cast<float>(this->m_height); }

void Application::run() {
    this->m_is_running = true;

    while (this->m_is_running) {
        SDL_Event event;

        Uint64 start_work_delta = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                this->m_is_running = false;
                Logger::debug("Application: Quit");
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
                MouseAndKeyboard::onKeyDown(event.key.key);
                for (const auto &callback: this->m_callbacks_keyPress) {
                    callback(event.key);
                }
            } else if (event.type == SDL_EVENT_KEY_UP) {
                MouseAndKeyboard::onKeyUp(event.key.key);
            } else if (event.type == SDL_EVENT_MOUSE_MOTION) {
                *MouseAndKeyboard::mouse_x = static_cast<int>(event.motion.x);
                *MouseAndKeyboard::mouse_y = static_cast<int>(event.motion.y);
            }
        }

        if (this->m_is_running) {
            // scene scoped on update
            this->scene_manager->callOnUpdateCallback(SDL_GetTicks());
            // global on update
            for (const auto &callback: this->m_callbacks_update) {
                callback(SDL_GetTicks());
            }

            this->scene_manager->renderScene();
            auto work_duration = static_cast<float>(SDL_GetTicks() - start_work_delta);
            if (work_duration > this->m_interval_between_drawcall) {
                work_duration = this->m_interval_between_drawcall;
            }
            const auto delay = static_cast<Uint32>(this->m_interval_between_drawcall - work_duration);
            SDL_Delay(delay);
        }
    }
}

void Application::stop() { this->m_is_running = false; }

void Application::register_update_callback(const std::function<void(Uint64 delta)> &update_callback) {
    this->m_callbacks_update.push_back(update_callback);
}

void Application::register_keyPress_callback(const std::function<void(SDL_KeyboardEvent event)> &keyPress_callback) {
    this->m_callbacks_keyPress.push_back(keyPress_callback);
}

Application *Application::Application::m_instance = nullptr;
