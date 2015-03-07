#pragma once

#include "game.h"
#include "texture.h"



namespace ykf {

struct GameObject {
public:
    virtual ~GameObject ( ) { }

    virtual void handle_events ( ) = 0;

    virtual void init ( ) = 0;

    virtual void update ( ) = 0;

    /**
     * Renders this game object
     */
    void render (SDL_Renderer* renderer) {
        auto texture = TextureManager::Instance ( ).get (_texture_id);
        
        SDL_RenderCopyEx (renderer,
                          texture,
                          &_txt_rect,
                          &_rdr_rect,
                          0, 0,
                          SDL_FLIP_HORIZONTAL);
    }


protected:
    std::string _texture_id;

    // rectangle used over the texture
    SDL_Rect    _txt_rect;

    // rectangle used over the rendering area
    SDL_Rect    _rdr_rect;
};

}
