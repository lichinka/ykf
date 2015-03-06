#include <string>

#include <SDL2/SDL.h>



namespace ykf {

struct Game {
public:
    // the screen dimensions double the size of a C64 
    static const int WIDTH  = 640;
    static const int HEIGHT = 400;

    Game ( ) : _closed      (true),
               _initialized (false),
               _renderer    (nullptr),
               _window      (nullptr) { }

    ~Game ( ) {
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
                                        Game::WIDTH, 
                                        Game::HEIGHT,
                                        SDL_WINDOW_SHOWN);
            if (_window != nullptr) {
                // create a renderer over the main window
                _renderer = SDL_CreateRenderer (_window, 
                                                -1,
                                                SDL_RENDERER_ACCELERATED);
                if (_renderer != nullptr) {
                    SDL_SetRenderDrawColor (_renderer,
                                            255, 255, 255,  // RGB
                                            255);           // Alpha
                    _initialized = true;
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
    SDL_Window*     _window;
};

}
