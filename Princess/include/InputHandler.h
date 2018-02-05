#pragma once

#include <SDL.h>
#include "EventListener.h"

class InputHandler
{
public:
	InputHandler(EventListener *e, SDL_Event * ev) { m_eventListener = e; m_event = ev; };

	void handleInput();

private:
	EventListener *m_eventListener;
	SDL_Event * m_event;
};