#include "scene_manager.h"
#include "scene.h"

SceneManager::SceneManager(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    this->m_renderer = renderer;
}

SceneManager::~SceneManager() {
    // TODO delete all scenes
    // TODO delete renderer
}

SDL_Renderer* SceneManager::getRenderer() {
    return this->m_renderer;
}

void SceneManager::addScene(std::string key, Scene* scene) {
    this->scenes_by_id.insert({key, scene});
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

void SceneManager::renderScene() {
    Scene* scene = this->getActiveScene();
    if(scene != nullptr) {
        scene->renderAllObjects(this->m_renderer);
    }
}