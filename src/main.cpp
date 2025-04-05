#include "./engine/application.h"
#include "./game/menu_scene.cpp"
#include "./game/game_scene.cpp"

int main() {
  Application* application = Application::createInstance("Spaceship", 800, 600);
  MenuScene* menu_scene = new MenuScene();
  GameScene *game_scene = new GameScene();
  application->scene_manager->addScene("menu", menu_scene);
  application->scene_manager->addScene("game", game_scene);
  application->run();
  return 0;
}