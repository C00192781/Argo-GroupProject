#include "InputHandler.h"

void InputHandler::handleInput(SDL_Event &e, SDL_Point &pos) 
{
	switch (e.type) {
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_w:
			pos.y--;
			break;

		case SDLK_a:
			pos.x--;
			break;

		case SDLK_s:
			pos.y++;
			break;

		case SDLK_d:
			pos.x++;
			break;

		case SDLK_d && SDLK_s:
			pos.y++;
			pos.x++;
			break;
		}
		break;
	}
}