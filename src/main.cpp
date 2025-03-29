#include "./engine/application.h"
#include "./game/spaceship.cpp"

int main() {
  Application* application = Application::createInstance("Spaceship", 800, 600);
  Spaceship* spaceship = new Spaceship();
  application->run();
  delete spaceship;
  return 0;
}