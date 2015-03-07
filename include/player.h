#pragma once

#include "constants.h"
#include "game_object.h"



namespace ykf {

struct Player : GameObject {
public:
    Player ( ) { }

    ~Player ( ) { }

    /**
     * Initializes this player
     */
    void init ( ) {
        _texture_id = "characters";

        // coordinates to extract this player's sprite from the texture map
        _txt_rect.x = 0;
        _txt_rect.y = 4;
        _txt_rect.w = 16;
        _txt_rect.h = 36;

        // coordinates over the rendering plane
        _rdr_rect.x = 10 * WIN_ZOOM;
        _rdr_rect.y = 35 * WIN_ZOOM;
        _rdr_rect.w = _txt_rect.w * WIN_ZOOM;
        _rdr_rect.h = _txt_rect.h * WIN_ZOOM;
    }

    void handle_events ( ) {
    }

    /** 
     * Updates the state of this player
     */
    void update ( ) {
        // change the animation frame
        if (_txt_rect.x == 0)
            _txt_rect.x = 29;
        else
            _txt_rect.x = 0;

        // move the target position
        _rdr_rect.x += 3 * WIN_ZOOM;
    }

    void render (SDL_Renderer* renderer) {
        GameObject::render (renderer);
    }
};

}
