#include <iostream>
#include <SDL3/SDL.h>
#include "application.cpp"
#include "texture.cpp"


SDL_FRect drect = {0, 0, 48, 48};
SDL_Texture* tex = nullptr;


void onRenderCallback(Application* application, SDL_Window* window,SDL_Renderer* renderer) {
  std::cout << "Render" << std::endl;

  try {
    if (tex == nullptr) {
      tex = loadTexture(renderer, "../assets/img/spaceship.bmp");
    }

    SDL_RenderClear(renderer);
    const SDL_FRect frect = {0, 0, 48, 48};
    SDL_RenderTextureRotated(renderer, tex, &frect, &drect, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);

  } catch (std::runtime_error e) {
    std::cerr << e.what() << std::endl;
    SDL_DestroyRenderer(renderer);
    application->stop();
    SDL_DestroyWindow(window);
    SDL_Quit();
  }
}

void onKeyboardPressDown(SDL_KeyboardEvent event) {
  if (event.key == SDLK_LEFT) {
      drect.x--;
    } else if (event.key == SDLK_RIGHT) {
      drect.x++;
    }
}


int main(int argc, char* argv[]) {
  Application* application = Application::getInstance("Spaceship", 800, 600);
  application->onRender(onRenderCallback);
  application->onKeyEventDown(onKeyboardPressDown);
  application->run();
  return 0;
}