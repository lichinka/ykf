#pragma once

#include "game.h"
#include "texture.h"



namespace ykf {

struct GameObject {
public:
    virtual ~GameObject ( ) { }

    virtual void handle_event ( ) = 0;
    virtual void init         ( ) = 0;
    virtual void update       ( ) = 0;
    virtual void render       (SDL_Renderer* renderer,
                               SDL_RendererFlip flip=SDL_FLIP_NONE);


protected:
    std::string     _texture_id;

    // rectangle used over the texture
    SDL_Rect        _txt_rect;

    // rectangle used over the rendering area
    SDL_Rect        _rdr_rect;
    float           _velocity;
};



/**
 * Renders this game object using the received ``renderer``
 */
void GameObject::render (SDL_Renderer* renderer,
                         SDL_RendererFlip flip) {
    auto texture = TextureManager::Instance ( ).get (_texture_id);
    
    SDL_RenderCopyEx (renderer,
                      texture,
                      &_txt_rect,
                      &_rdr_rect,
                      0, 0,
                      flip);
}

}
