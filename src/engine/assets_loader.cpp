#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include "application.h"
#include "logger.h"

namespace AssetsLoaders {
    std::map<std::string, SDL_Texture*> textures_by_path;

    SDL_Texture* getTextureFromCache(const std::string bmpFilePath) {
        auto it = textures_by_path.find(bmpFilePath);
        if (it == textures_by_path.end()) return nullptr;
        return it->second;

        // May insert a default entry as nullptr if key doesn't exist 
        // Risky when clearing all assets by key iteration (clearing a nullptr) 
        // See https://en.cppreference.com/cpp/container/map/operator_at
        // return textures_by_path[bmpFilePath]; 
    }

    void setTextureInCache(const std::string bmpFilePath, SDL_Texture* texture) {
        if (textures_by_path.count(bmpFilePath)) {
          SDL_DestroyTexture(textures_by_path[bmpFilePath]);
        }
        textures_by_path[bmpFilePath] = texture;
    }

    bool hasTextureInCache(const std::string bmpFilePath) {
        auto iterator = textures_by_path.find(bmpFilePath);
        return iterator != textures_by_path.end();
    }

    SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string bmpFilePath) {
        if (hasTextureInCache(bmpFilePath)) {
            // if the texture was already loaded return it from cache
            Logger::debug("AssetsLoader: Loading texture from cache (" + bmpFilePath + ")");
            return getTextureFromCache(bmpFilePath);
        }

        SDL_Surface* bmp = nullptr;
        SDL_Texture* tex = nullptr;

        bmp = SDL_LoadBMP(bmpFilePath.c_str());

        if (bmp == nullptr) {
            throw std::runtime_error("SDL_LoadBMP Error: " + std::string(SDL_GetError()));
        }

        Logger::debug("AssetsLoader: Loading texture (" + bmpFilePath + ")");
        tex = SDL_CreateTextureFromSurface(renderer, bmp);
        SDL_DestroySurface(bmp);

        if (tex == nullptr) {
            throw std::runtime_error("SDL_LoadBMP Error: " + std::string(SDL_GetError()));
        }

        setTextureInCache(bmpFilePath, tex);
        return tex;
    }

    void loadTexturesInCache(std::vector<std::string> texture_paths) {
        for(auto path : texture_paths) {
            loadTexture(
                    Application::getInstance()->scene_manager->getRenderer(),
                    path
            );
        }
    }

    void clearTexturesFromCache() {
        for (auto & it : textures_by_path) {
            if(it.second != nullptr) {
                SDL_DestroyTexture(it.second);
            }
        }
        textures_by_path.clear();
    }

    std::string getAsset(const std::string filePath) {
        const char* base = SDL_GetBasePath();
        return std::string(base) + "../../assets/" + filePath;
    }
}