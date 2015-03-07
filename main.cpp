#include "game.h"



int main (int argc, char* args[])
{
#ifdef NDEBUG
    SDL_LogSetAllPriority (SDL_LOG_PRIORITY_WARN);
#else
    SDL_LogSetAllPriority (SDL_LOG_PRIORITY_INFO);
#endif
    // a game object
    auto g_game = new ykf::Game ( );

	if (g_game->init ("YKF")) {
        g_game->run ( );
	}

	// free resources before exiting
	g_game->close ( );

	return EXIT_SUCCESS;
}
