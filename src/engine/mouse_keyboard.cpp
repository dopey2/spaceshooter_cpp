#include <vector>
#include <bits/stdc++.h>
#include <SDL3/SDL.h>
#include "mouse_keyboard.h"

static int internal_mouse_x = 0;
static int internal_mouse_y = 0;

namespace MouseAndKeyboard {
   std::vector<SDL_Keycode> keys_down;
   int* mouse_x = &internal_mouse_x;
   int* mouse_y = &internal_mouse_y;

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

  void setMouseX(int x) {
      *mouse_x = x;
  }
}