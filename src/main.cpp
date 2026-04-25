#include "./engine/__engine.h"
#include "./game/scenes/game_scene.hpp"
#include "./game/scenes/menu_scene.hpp"

int main() {
  Application* application = Application::createInstance("Spaceship", 800, 600);

  Logger::debug(SDL_GetBasePath());

  AssetsLoaders::loadTexturesInCache({
    AssetsLoaders::getAsset("img/hand_made_spaceship.bmp"), 
    AssetsLoaders::getAsset("img/fire_bullet_default.bmp"),
    AssetsLoaders::getAsset("img/fire_bullet_blue.bmp"),
    AssetsLoaders::getAsset("img/asteroid.bmp"),
    AssetsLoaders::getAsset("img/bg.bmp"),
  });
  MenuScene* menu_scene = new MenuScene();
  GameScene *game_scene = new GameScene();
  application->scene_manager->addScene("menu", menu_scene);
  application->scene_manager->addScene("game", game_scene);
  application->run();
  delete application;
  // Do note delete scenes manually 
  // SceneManager tooked the ownership and that care of that
  return 0;
}