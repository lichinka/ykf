#pragma once

#include <SDL2/SDL_keycode.h>



namespace ykf {

struct InputHandler {
public:
    /**
     * Returns the singleton instance of this class
     */
    static InputHandler& Instance ( ) {
        // instantiated on first use and guaranteed to be destroyed
        static InputHandler instance;
        return instance;
    }

    bool is_key_down        (SDL_Scancode key);
    bool is_key_up          (SDL_Scancode key);
    void set_keyboard_state (const uint8_t* ks) {
       _key_state = ks;
    }


private:
    const uint8_t* _key_state;

    // avoid external instantiation of this class
    InputHandler ( ) : _key_state (nullptr) { }
    InputHandler (InputHandler const&)   = delete;
    void operator =(InputHandler const&) = delete;
};


/**
 * Checks if the key with code ``key`` has been pressed
 */
bool InputHandler::is_key_down (SDL_Scancode key) {
    if (_key_state != nullptr) {
        return (_key_state[key] == 1);
    } else {
        return false;
    }
}


/**
 * Checks if the key with code ``key`` has been released
 */
bool InputHandler::is_key_up (SDL_Scancode key) {
    if (_key_state != nullptr) {
        return (_key_state[key] == 0);
    } else {
        return false;
    }
}
}
