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
    for (auto const& iterator : this->scenes_by_id)
    {
        std::cout << "SCENE_MANAGER: Deleting scene " << iterator.first  << std::endl;
        if (iterator.second != nullptr) {
            delete iterator.second;
        }

        SDL_DestroyRenderer(this->m_renderer);
        this->m_renderer = nullptr;
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
}


void SceneManager::renderScene() {
    Scene* scene = this->getActiveScene();
    if(scene != nullptr) {
        scene->renderAllObjects(this->m_renderer);
    }
}
