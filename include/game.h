#pragma once

#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include "player.h"
#include "texture.h"
#include "constants.h"
#include "game_object.h"



namespace ykf {


struct Game {
private:
    bool            _closed;
    bool            _initialized;
    bool            _running;
    SDL_Renderer*   _renderer;
    SDL_Window*     _window;

    // all game objects are kept here
    std::vector<GameObject*> _objects;


    /**
     * Loads game objects
     */
    void _load_objects ( ) {
        auto player = new Player ( );

        player->init ( );
        _objects.push_back (player);
    }


    /**
     * Handles input events
     */
    void _handle_events ( ) {
        SDL_Event event;

        if (SDL_PollEvent (&event)) {
            switch (event.type) {
                // stop the game
                case SDL_QUIT:
                    _running = false;
                    close ( );
                    break;

                default:
                    break;
            }
        }
    }


    void _update ( ) {
        for (auto& go : _objects)
            go->update ( );
    }


    void _render ( ) {
        SDL_RenderClear (_renderer);

        for (auto& go : _objects)
            go->render (_renderer);

        SDL_RenderPresent (_renderer);
    }


public:
    Game ( ) : _closed      (true),
               _initialized (false),
               _running     (false),
               _renderer    (nullptr),
               _window      (nullptr) { }

    ~Game ( ) {
        for (auto& go : _objects)
            delete (go);

        if (!_closed)
            close ( );
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
                                        WIN_WIDTH  * WIN_ZOOM, 
                                        WIN_HEIGHT * WIN_ZOOM,
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
                    _initialized = TextureManager::Instance ( ).load ("characters.png",
                                                                      "characters",
                                                                      _renderer);
                    _closed      = !_initialized;

                    // load game objects
                    _load_objects ( );
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


    /**
     * Runs the main game loop
     */
    void run ( ) {
        if (!_running) {
            _running = true;

            while (_running) {
                _handle_events ( );
                _update ( );
                _render ( );

                // refresh rate at 10 frames/second
                SDL_Delay (100);
            }
        }
    }

    
    /**
     * Pauses the main game loop
     */
    void pause ( ) {
        _running = false;
    }
};

}

