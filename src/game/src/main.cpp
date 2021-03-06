
#include "Globals.h"
#include "Texture.h"
#include "game/scenes/GameSceneMain.h"
#include <cassert>
#include <cstdio>
#include <array>
#include <string>

namespace
{
	void init()
	{
		global::instance.init();
	}
}

int main(int argc, char* args[])
{
	// satisfy compiler warning for not referencing parameters
	for (int i = 0; i < argc; ++i)
	{
		printf("command line args %u %s\n", i, args[i]);
	}

	// initialise SDL and other systems such as font and PNG loading
	init();

	printf("SDL Initialisation complete\n");

	
	
	std::unique_ptr<rcgf::IGameScene> gameState = std::make_unique<game::GameSceneMain>();

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		// handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			// user requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				gameState->keyDown(e.key.keysym.sym);
			}
			else if (e.type == SDL_KEYUP)
			{
				gameState->keyUp(e.key.keysym.sym);
			}
		}

		// clear screen
		SDL_SetRenderDrawColor(global::instance.getRenderer(), 0x00, 0x00, 0x20, 0xFF);
		SDL_RenderClear(global::instance.getRenderer());

		gameState->update();
		if (gameState->hasPendingState())
		{
			gameState = gameState->popPendingState();
		}
		else
		{
			gameState->render();
		}

		//Update screen
		SDL_RenderPresent(global::instance.getRenderer());
	}

	return 0;
}
