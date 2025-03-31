#include <vector>
#include <bits/stdc++.h>
#include <SDL3/SDL.h>
#include "keyboard.h"

namespace Keyboard {
  std::vector<SDL_Keycode> keys_down;

  void onKeyDown(SDL_Keycode key) {
    auto iterator = find(keys_down.begin(), keys_down.end(), key);
    if (iterator == keys_down.end()) {
      keys_down.push_back(key);
    }
  }

  void onKeyUp(SDL_Keycode key) {
    auto iterator = find(keys_down.begin(), keys_down.end(), key);
    if (iterator != keys_down.end()) {
      keys_down.erase(iterator);
    }
  }

  bool isKeyDown(SDL_Keycode key) {
    auto iterator = find(keys_down.begin(), keys_down.end(), key);
    return iterator != keys_down.end();
  }
}

