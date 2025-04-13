#include "scene_manager.h"
#include "scene.h"
#include "logger.h"

SceneManager::SceneManager(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    if (renderer == nullptr) {
        Logger::error("SceneManager: Renderer could not be created !");
        Logger::error("SDL_Error: " + (std::string)SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    this->m_renderer = renderer;
}

SceneManager::~SceneManager() {
    SDL_DestroyRenderer(this->m_renderer);
    this->m_renderer = nullptr;
    for (auto const& iterator : this->scenes_by_id)
    {
        Logger::debug("SceneManager: Deleting scene " + iterator.first);
        if (iterator.second != nullptr) {
            delete iterator.second;
        }
    }
}

SDL_Renderer* SceneManager::getRenderer() {
    return this->m_renderer;
}

void SceneManager::addScene(std::string key, Scene* scene) {
    this->scenes_by_id.insert({key, scene});
    // the first scene becomes the active scene
    if(scenes_by_id.size() == 1) {
        this->active_scene = key;
    }
}

Scene* SceneManager::getActiveScene() {
    auto it = this->scenes_by_id.find(this->active_scene);
    if (it != this->scenes_by_id.end()) {
        return this->scenes_by_id.at(this->active_scene);
    }
    return nullptr;
}

void SceneManager::setActiveScene(std::string key) {
    this->active_scene = key;
    Scene* active_scene = this->getActiveScene();
    active_scene->onActive();
}

void SceneManager::callOnUpdateCallback(Uint64 delta) {
    Scene* activeScene = this->getActiveScene();
    if (activeScene != nullptr) {
        activeScene->callOnUpdateCallback(delta);
    }
}

void SceneManager::renderScene() {
    Scene* scene = this->getActiveScene();
    if(scene != nullptr) {
        scene->renderAllObjects(this->m_renderer);
    }
}
