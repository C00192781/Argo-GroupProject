#include "InputHandler.h"

void InputHandler::handleInput(SDL_Event &e)
{
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		switch (e.button.button)
		{
		case SDL_BUTTON_LEFT:
			m_eventListener->LeftClick = true;
			break;
		case SDL_BUTTON_RIGHT:
			m_eventListener->RightClick = true;
			break;

		default:
			break;
		}
		break;

	case SDL_MOUSEBUTTONUP:
		switch (e.button.button)
		{
		case SDL_BUTTON_LEFT:
			m_eventListener->LeftClick = false;
			break;
		case SDL_BUTTON_RIGHT:
			m_eventListener->RightClick = false;
			break;

		default:
			break;
		}
		break;

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			m_eventListener->W = true;
			break;

		case SDLK_a:
			m_eventListener->A = true;
			break;

		case SDLK_s:
			m_eventListener->S = true;
			break;

		case SDLK_d:
			m_eventListener->D = true;
			break;

		case SDLK_ESCAPE:
			m_eventListener->Escape = true;
			break;

		case SDLK_SPACE:
			m_eventListener->Space = true;
			break;

		default:
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			m_eventListener->W = false;
			break;

		case SDLK_a:
			m_eventListener->A = false;
			break;

		case SDLK_s:
			m_eventListener->S = false;
			break;

		case SDLK_d:
			m_eventListener->D = false;
			break;

		case SDLK_ESCAPE:
			m_eventListener->Escape = false;
			break;

		case SDLK_SPACE:
			m_eventListener->Space = false;
			break;

		default:
			break;
		}
		break;
	}
}