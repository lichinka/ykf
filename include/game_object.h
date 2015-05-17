#pragma once

#include "game.h"
#include "texture.h"
#include "vector2d.h"



namespace ykf {

struct GameObject {
public:
    virtual ~GameObject ( ) { }

    virtual void handle_event ( ) = 0;
    virtual void init         ( ) = 0;
    virtual void update       ( ) = 0;
    virtual void render       (SDL_Renderer* renderer);


protected:
    std::string      _texture_id;

    // rectangle use d over the texture
    SDL_Rect         _txt_rect;

    // rectangle use d over the rendering area
    SDL_Rect         _rdr_rect;

    // flip the rendered texture
    SDL_RendererFlip _flip;

    Vector2D<float>  _velocity;
    Vector2D<float>  _acceleration;
};



/**
 * Renders this game object using the received ``renderer``
 */
void GameObject::render (SDL_Renderer* renderer) {
    auto texture   = TextureManager::Instance ( ).get (_texture_id);
    auto zoom_rect = _rdr_rect;

    // adapt the rendering rectangle to the current window zoom
    zoom_rect.x *= WIN_ZOOM;
    zoom_rect.y *= WIN_ZOOM;
    zoom_rect.w *= WIN_ZOOM;
    zoom_rect.h *= WIN_ZOOM;

    SDL_RenderCopyEx (renderer,
                      texture,
                      &_txt_rect,
                      &zoom_rect,
                      0, 0,
                      _flip);
}

}
