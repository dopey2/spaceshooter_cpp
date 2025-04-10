#include "./engine/application.h"
#include "./engine/assets_loader.h"
#include "./game/game_scene.cpp"
#include "./game/menu_scene.cpp"

int main() {
  Application* application = Application::createInstance("Spaceship", 800, 600);
  AssetsLoaders::loadTexturesInCache({
   "../assets/img/hand_made_spaceship.bmp",
   "../assets/img/fire_bullet_default.bmp",
   "../assets/img/fire_bullet_blue.bmp",
   "../assets/img/asteroid.bmp",
   "../assets/img/bg.bmp"
  });
  MenuScene* menu_scene = new MenuScene();
  GameScene *game_scene = new GameScene();
  application->scene_manager->addScene("menu", menu_scene);
  application->scene_manager->addScene("game", game_scene);
  application->run();
  return 0;
}