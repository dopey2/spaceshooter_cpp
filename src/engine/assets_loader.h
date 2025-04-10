#pragma once

#include <map>
#include <string>
#include <SDL3/SDL.h>

namespace AssetsLoaders {
    SDL_Texture* getTextureFromCache(const std::string bmpFilePath);
    void setTextureInCache(const std::string bmpFilePath, SDL_Texture* texture);
    bool hasTextureInCache(const std::string bmpFilePath);
    SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string bmpFilePath);
    void loadTexturesInCache(std::vector<std::string> texture_paths);
}