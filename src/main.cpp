#include <SDL3/SDL.h>
#include "application.cpp"
#include "world.cpp"
#include "renderer_mediator.cpp"
#include "sprite.cpp"


void onKeyboardPressDown(SDL_KeyboardEvent event) {
  if (event.key == SDLK_LEFT) {
      // TODO
    } else if (event.key == SDLK_RIGHT) {
      // TODO
    }
}


int main(int argc, char* argv[]) {
  Application* application = new Application("Spaceship", 800, 600);
  World* world = new World();
  Sprite* spaceship = new Sprite("../assets/img/spaceship.bmp");
  world->addObject(spaceship);
  RendererMediator* renderer = new RendererMediator(application, world);

  // application->onKeyEventDown(onKeyboardPressDown);
  application->run();
  return 0;
}