#include "game.h"



int main (int argc, char* args[])
{
    // a game object
    auto g_game = new ykf::Game ( );

	if (g_game->init ("YKF")) {
        SDL_Delay (3000);
	}

	// free resources before exiting
	g_game->close ( );

	return EXIT_SUCCESS;
}
