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
};



/**
 * Initializes this player
 */
void Player::init ( ) {
    _texture_id = "characters";

    // coordinates to extract the player's sprite from the texture map
    _txt_rect.x = 0;
    _txt_rect.y = 2;
    _txt_rect.w = 16;
    _txt_rect.h = 42;

    // coordinates over the rendering plane
    _rdr_rect.x = 10;
    _rdr_rect.y = 45;
    _rdr_rect.w = _txt_rect.w;
    _rdr_rect.h = _txt_rect.h;

    // initial acceleration and velocity
    _acceleration = GRAVITY;
    _velocity.set (0.0f, 0.0f);
}


/**
 * Makes this player react to external events
 */
void Player::handle_event ( ) {
    Vector2D<float> vel;

    // right
    if (InputHandler::Instance ( ).is_key_down (SDL_SCANCODE_RIGHT)) {
        _acceleration = GRAVITY;
        _velocity.set (4.0f, 0.0f);
        _flip     = SDL_FLIP_HORIZONTAL;
    // left
    } else if (InputHandler::Instance ( ).is_key_down (SDL_SCANCODE_LEFT)) {
        _acceleration = GRAVITY;
        _velocity.set (-4.0f, 0.0f);
        _flip     = SDL_FLIP_NONE;
    // up
    } else if (InputHandler::Instance ( ).is_key_down (SDL_SCANCODE_UP)) {
        _acceleration.y = -2.0f;
    } else
        _velocity.set (0.0f, 0.0f);
}


/** 
 * Updates the state of this player
 */
void Player::update ( ) {
    // change the animation frame based on the velocity
    if (_velocity.x == 0.0f) {
        _txt_rect.x = 58;
    } else {
        // alternate walking frames
        if (_txt_rect.x == 0)
            _txt_rect.x = 29;
        else
            _txt_rect.x = 0;
    }
    // move the target position
    _velocity   += _acceleration;
    _rdr_rect.x += _velocity.x;
    _rdr_rect.y += _velocity.y;

    // update the acceleration
    if (_acceleration.y < 0.0f)
        _acceleration = GRAVITY;

    // make sure we are not out of the rendering area
    if (_rdr_rect.x < 0)
        _rdr_rect.x = 0;
    if (_rdr_rect.x > WIN_WIDTH)
        _rdr_rect.x = WIN_WIDTH;
    if (_rdr_rect.y < 0)
        _rdr_rect.y = 0;
    if (_rdr_rect.y + _rdr_rect.h > WIN_HEIGHT)
        _rdr_rect.y = WIN_HEIGHT - _rdr_rect.h;
}

}
