#pragma once
#include <vector>
#include <functional>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>

class Application;

class MouseAndKeyboard {
    friend class Application;

    private:
        static int _mouse_x;
        static int _mouse_y;
        static std::vector<SDL_Keycode> keys_down;

        // a list of listeners who watches for key press
        static std::vector<std::function<void(SDL_KeyboardEvent)>> keypress_listeners;
        // should only be used by Application to inject fresh value
        static void processInputEvent(const SDL_Event& event);
        static void clearListeners();

    public:
        // external read only values
        // should point to the private internal _mouse_x & _mouse_y
        static const int& mouse_x;
        static const int& mouse_y;

        // return true if the given key is down
        static bool isKeyDown(SDL_Keycode key);

        static void addKeyPressListener(const std::function<void(SDL_KeyboardEvent event)> &keyPress_callback);
};
