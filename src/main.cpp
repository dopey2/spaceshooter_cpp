#include "./engine/__engine.h"
#include "./game/scenes/game_scene.hpp"
#include "./game/scenes/menu_scene.hpp"

int main() { 
  // app settings
  constexpr auto width = 800;
  constexpr auto height = 600;
  constexpr auto targetFps = 60;

  Application* application = Application::createInstance(
    "Spaceship",
    width,
    height,
    targetFps
  );

  // preload assets
  AssetsLoaders::loadTexturesInCache({
    AssetsLoaders::getAsset("img/hand_made_spaceship.bmp"), 
    AssetsLoaders::getAsset("img/fire_bullet_default.bmp"),
    AssetsLoaders::getAsset("img/fire_bullet_blue.bmp"),
    AssetsLoaders::getAsset("img/asteroid.bmp"),
    AssetsLoaders::getAsset("img/bg.bmp"),
  });

  // scenes creation
  // do note delete scenes manually, SceneManager takes ownership over it and handle it implicitely 
  auto* menu_scene = new MenuScene();
  auto *game_scene = new GameScene();
  application->scene_manager->addScene("menu", menu_scene);
  application->scene_manager->addScene("game", game_scene);

  // start app
  // application being a singleton must be deleted manually after it stops running
  application->run();
  delete application;
  return 0;
}
