#include <iostream>
#include <map>
#include <string>
#include <SDL3/SDL.h>

namespace AssetsLoaders {
    std::map<std::string, SDL_Texture*> textures_by_path;

    SDL_Texture* getTextureFromCache(const std::string bmpFilePath) {
        return textures_by_path[bmpFilePath];
    }

    void setTextureInCache(const std::string bmpFilePath, SDL_Texture* texture) {
        textures_by_path[bmpFilePath] = texture;
    }

    bool hasTextureInCache(const std::string bmpFilePath) {
        auto iterator = textures_by_path.find(bmpFilePath);
        return iterator != textures_by_path.end();
    }

    SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* bmpFilePath) {
        if (hasTextureInCache(bmpFilePath)) {
            // if the texture was already loaded return it from cache
            return getTextureFromCache(bmpFilePath);
        }

        SDL_Surface* bmp = nullptr;
        SDL_Texture* tex = nullptr;

        bmp = SDL_LoadBMP(bmpFilePath);

        if (bmp == nullptr) {
            throw std::runtime_error("SDL_LoadBMP Error: " + std::string(SDL_GetError()));
        }

        tex = SDL_CreateTextureFromSurface(renderer, bmp);
        SDL_DestroySurface(bmp);

        if (tex == nullptr) {
            throw std::runtime_error("SDL_LoadBMP Error: " + std::string(SDL_GetError()));
        }

        setTextureInCache(bmpFilePath, tex);
        return tex;
    }
}