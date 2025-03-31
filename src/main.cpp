#include "./engine/application.h"
#include "./game/space_controller.cpp"

int main() {
  Application* application = Application::createInstance("Spaceship", 800, 600);
  SpaceController* spaceController = new SpaceController();
  application->run();
  delete spaceController;
  spaceController = nullptr;
  return 0;
}