#include <SDL3/SDL.h>
#include "./engine/application.cpp"
#include "./engine/sprite.cpp"


void setup(Application* application) {
  Sprite* spaceship = new Sprite("../assets/img/spaceship.bmp");
  application->scene->addObject(spaceship);
  spaceship->setX(application->getWidth() / 2 - 48);
  spaceship->setY(application->getHeight() - 48);

  application->register_keyPress_callback([=](SDL_KeyboardEvent event) -> void {
    if (event.key == SDLK_LEFT) {
     spaceship->setX(spaceship->x - 1);
   } else if (event.key == SDLK_RIGHT) {
     spaceship->setX(spaceship->x + 1);
   }
  });
}


int main(int argc, char* argv[]) {
  Application* application = Application::getInstance("Spaceship", 800, 600);
  setup(application);
  application->run();
  return 0;
}