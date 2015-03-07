#pragma once

#include "input.h"
#include "constants.h"
#include "game_object.h"



namespace ykf {

struct Player : GameObject {
public:
    Player ( ) { }

    ~Player ( ) { }

    void init         ( );
    void handle_event ( );
    void update       ( );
    void render       (SDL_Renderer* renderer,
                       SDL_RendererFlip flip=SDL_FLIP_NONE);
};



/**
 * Initializes this player
 */
void Player::init ( ) {
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

    // initial velocity
    _velocity   = 0.0f;
}


/**
 * Makes this player react to external events
 */
void Player::handle_event ( ) {
    if (InputHandler::Instance ( ).is_key_down (SDL_SCANCODE_RIGHT))
        _velocity = 2.5f;
    else if (InputHandler::Instance ( ).is_key_down (SDL_SCANCODE_LEFT))
        _velocity = -2.5f;
    else
        _velocity = 0.0f;
}


/** 
 * Updates the state of this player
 */
void Player::update ( ) {
    // change the animation frame based on the velocity
    if (_velocity == 0.0f) {
        _txt_rect.x = 58;
    } else {
        // alternate walking frames
        if (_txt_rect.x == 0)
            _txt_rect.x = 29;
        else
            _txt_rect.x = 0;
    }
    // move the target position
    _rdr_rect.x += _velocity * WIN_ZOOM;
}


/**
 * Renders this player using the received ``renderer``
 */
void Player::render (SDL_Renderer* renderer,
                     SDL_RendererFlip flip) {
    if (_velocity >= 0)
        flip = SDL_FLIP_HORIZONTAL;

    GameObject::render (renderer,
                        (SDL_RendererFlip) flip);
}

}
