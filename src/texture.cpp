#include <SDL3/SDL.h>
#include <iostream>

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* bmpFilePath) {
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

    return tex;
}