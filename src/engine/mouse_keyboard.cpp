#include "mouse_keyboard.h"
#include <algorithm>

int MouseAndKeyboard::_mouse_x = 0;
int MouseAndKeyboard::_mouse_y = 0;
std::vector<SDL_Keycode> MouseAndKeyboard::keys_down;
std::vector<std::function<void(SDL_KeyboardEvent)>> MouseAndKeyboard::keypress_listeners;

const int& MouseAndKeyboard::mouse_x = MouseAndKeyboard::_mouse_x;
const int& MouseAndKeyboard::mouse_y = MouseAndKeyboard::_mouse_y;


void MouseAndKeyboard::processInputEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        const SDL_Keycode key = event.key.key;

        // notify all listeners
        for (const auto &callback: MouseAndKeyboard::keypress_listeners) {
            callback(event.key);
        }

        // set current key down
        auto iterator = std::find(keys_down.begin(), keys_down.end(), key);
        if (iterator == keys_down.end()) {
          keys_down.push_back(key);
        }
    } else if (event.type == SDL_EVENT_KEY_UP) {
        const SDL_Keycode key = event.key.key;

        // set current key up
        auto iterator = std::find(keys_down.begin(), keys_down.end(), key);
        if (iterator != keys_down.end()) {
            keys_down.erase(iterator);
        }
    } else if (event.type == SDL_EVENT_MOUSE_MOTION) {
        // update internal mouse position
        _mouse_x = static_cast<int>(event.motion.x);
        _mouse_y = static_cast<int>(event.motion.y);
    }
}


void MouseAndKeyboard::clearListeners() {
    MouseAndKeyboard::keypress_listeners.clear();
}

bool MouseAndKeyboard::isKeyDown(const SDL_Keycode key) {
    auto iterator = std::find(keys_down.begin(), keys_down.end(), key);
    return iterator != keys_down.end();
}

void MouseAndKeyboard::addKeyPressListener(const std::function<void(SDL_KeyboardEvent event)> &keyPress_callback) {
    MouseAndKeyboard::keypress_listeners.push_back(keyPress_callback);
}
