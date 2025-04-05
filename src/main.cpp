#include "./engine/application.h"
#include "./game/menu_scene.cpp"

int main() {
  Application* application = Application::createInstance("Spaceship", 800, 600);
  MenuScene* menu_scene = new MenuScene();
  application->scene_manager->addScene("menu", menu_scene);
  application->run();
  return 0;
}