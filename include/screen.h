#include <SDL2/SDL_log.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_window.h>


namespace ykf {

struct Screen {
public:
    // the screen dimensions are double the size of a C64 
    const int WIDTH  = 640;
    const int HEIGHT = 400;

    Screen() : _initialized (false),
               _closed      (true) { }
    ~Screen() {
        if (!_closed)
            close ( );
    }

    /**
     * Closes the active window
     */
    bool close() {
        if (_initialized) {
            _closed = false;

            //Deallocate surface
            SDL_FreeSurface (gHelloWorld);
            gHelloWorld = NULL;

            SDL_DestroyWindow (gWindow);
            gWindow = NULL;

            //Quit SDL subsystems
            SDL_Quit ( );
            _closed      = true;
            _initialized = !_closed;
        }
    }

    /**
     * Opens a new window
     */
    bool init (std::string title) {
        _initialized = false;
        _closed      = !_initialized;

        // Initialize SDL
        if (SDL_Init (SDL_INIT_VIDEO) < 0) {
            SDL_LogError (SDL_LOG_CATEGORY_VIDEO,
                          "SDL_Error: %s",
                          SDL_GetError ( ));
        } else {
            //Create window
            gWindow = SDL_CreateWindow (title.c_str(),
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        SCREEN_WIDTH, 
                                        SCREEN_HEIGHT, 
                                        SDL_WINDOW_SHOWN);
            if (gWindow == NULL) {
                SDL_LogError (SDL_LOG_CATEGORY_VIDEO,
                              "SDL_Error: %s",
                              SDL_GetError ( ));
            } else {
                //Get window surface
                gScreenSurface = SDL_GetWindowSurface( gWindow );
                _initialized = true;
                _closed      = !_initialized;
            }
        }
        return _initialized;
    }

private:
    bool _initialized;
    bool _closed;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;
        
    //The surface contained by the window
    SDL_Surface* gScreenSurface = NULL;

    //The image we will load and show on the screen
    SDL_Surface* gHelloWorld = NULL;
};

}


//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();


