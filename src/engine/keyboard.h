#pragma once

#include <vector>
#include <bits/stdc++.h>
#include <SDL3/SDL.h>

namespace Keyboard {
   void onKeyDown(SDL_Keycode key);
   void onKeyUp(SDL_Keycode key);
   bool isKeyDown(SDL_Keycode key);
}