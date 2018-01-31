#pragma once

#include <SDL.h>

class InputHandler
{
public:
	InputHandler() {}

	void handleInput(SDL_Event &e, SDL_Point &pos);
};