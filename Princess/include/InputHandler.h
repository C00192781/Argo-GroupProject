#pragma once

#include <SDL.h>
#include "EventListener.h"

class InputHandler
{
public:
	InputHandler(EventListener *e) { m_eventListener = e; };

	void handleInput(SDL_Event &e);

private:
	EventListener *m_eventListener;
};