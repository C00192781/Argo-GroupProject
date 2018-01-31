#include "InputHandler.h"

void InputHandler::handleInput(SDL_Event &e, SDL_Point &pos) 
{
	//if (e.key.keysym.sym == SDLK_w) {
	//	pos.y--;
	//}
	//if (e.key.keysym.sym == SDLK_a) {
	//	pos.x--;
	//}
	//if (e.key.keysym.sym == SDLK_s) {
	//	pos.y++;
	//}
	//if (e.key.keysym.sym == SDLK_d) {
	//	pos.x++;
	//}

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
		}
		break;
	}
}