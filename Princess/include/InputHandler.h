#pragma once

#include <SDL.h>
#include "EventListener.h"
#include <iostream>


class InputHandler
{
public:
	InputHandler(EventListener *e, SDL_Event * ev) { m_eventListener = e; m_event = ev; ControllerInit(); };

	void handleInput();
	void ControllerInit();

private:
	EventListener *m_eventListener;
	SDL_Event * m_event;
	#define MAX_CONTROLLERS 1
	SDL_GameController *gameController[MAX_CONTROLLERS];
	int MaxJoysticks;
	int ControllerIndex;
};