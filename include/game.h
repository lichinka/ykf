#pragma once

#include <string>

#include <SDL2/SDL.h>

#include "texture.h"



namespace ykf {

struct Game {
public:
    // the screen dimensions
    static const int WIDTH  = 320;
    static const int HEIGHT = 240;
    static const int ZOOM   = 2.0f;

    Game ( ) : _closed      (true),
               _initialized (false),
               _renderer    (nullptr),
               _window      (nullptr) { }

    ~Game ( ) {
        if (!_closed)
            close ( );
    }


    /**
     * Displays a sprite animation
     */
    void animation ( ) {
        SDL_Rect src_rect;
        SDL_Rect tgt_rect;
        auto texture = _texture_manager.get ("characters");

        src_rect.x =  0; src_rect.y = 4;
        src_rect.w = 16; src_rect.h = 36;

        tgt_rect.x = 30; tgt_rect.y = 100;
        tgt_rect.w = src_rect.w * Game::ZOOM;
        tgt_rect.h = src_rect.h * Game::ZOOM;
        
        for (int i = 0; i < 30; i ++) {
            SDL_RenderClear (_renderer);

            SDL_RenderCopyEx (_renderer,
                              texture,
                              &src_rect,
                              &tgt_rect,
                              0, 0,
                              SDL_FLIP_HORIZONTAL);

            SDL_RenderPresent (_renderer);
            if (i % 2 == 0) {
                src_rect.x  = 0;
            } else {
                src_rect.x = 29;
            }
            tgt_rect.x += 10;
            SDL_Delay (170);
        }
    }


    /**
     * Closes the active game
     */
    bool close ( ) {
        if (_initialized) {
            SDL_LogInfo (SDL_LOG_CATEGORY_SYSTEM,
                         "Closing game engine ...");

            // deallocate renderer and window
            SDL_DestroyRenderer (_renderer);
            SDL_DestroyWindow   (_window);

            // quit SDL subsystem
            SDL_Quit ( );
            _closed      = true;
            _initialized = !_closed;
        }
        return _closed;
    }


    /**
     * Initializes a new game
     */
    bool init (std::string title) {
        _initialized = false;
        _closed      = !_initialized;

        SDL_LogInfo (SDL_LOG_CATEGORY_SYSTEM,
                     "Initializing game engine ...");

        // initialize SDL
        if (SDL_Init (SDL_INIT_VIDEO) == 0) {
            // create the main window
            _window = SDL_CreateWindow (title.c_str(),
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        Game::WIDTH * Game::ZOOM, 
                                        Game::HEIGHT * Game::ZOOM,
                                        SDL_WINDOW_SHOWN);
            if (_window != nullptr) {
                // create a renderer over the main window
                _renderer = SDL_CreateRenderer (_window, 
                                                -1,
                                                SDL_RENDERER_ACCELERATED);
                if (_renderer != nullptr) {
                    SDL_SetRenderDrawColor (_renderer,
                                            0, 0, 0, 255); // RGB Alpha
                    // clear the window to black and show it
                    SDL_RenderClear (_renderer);
                    SDL_RenderPresent (_renderer);

                    // load textures
                    _initialized = _load_textures ( );
                    _closed      = !_initialized;
                } else {
                    SDL_LogError (SDL_LOG_CATEGORY_VIDEO,
                                  "SDL_Error: %s",
                                  SDL_GetError ( ));
                }
            } else {
                SDL_LogError (SDL_LOG_CATEGORY_VIDEO,
                              "SDL_Error: %s",
                              SDL_GetError ( ));
            }
        } else {
            SDL_LogError (SDL_LOG_CATEGORY_VIDEO,
                          "SDL_Error: %s",
                          SDL_GetError ( ));
        }
        return _initialized;
    }


private:
    bool            _closed;
    bool            _initialized;
    SDL_Renderer*   _renderer;
    TextureManager  _texture_manager;
    SDL_Window*     _window;


    /**
     * Loads game textures
     */
    bool _load_textures ( ) {
        return _texture_manager.load ("characters.png",
                                      "characters",
                                      _renderer);
    }
};

}
