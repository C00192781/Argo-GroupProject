#pragma once

#include <SDL.h>
#include "EventListener.h"

#include <iostream>

class InputHandler
{
public:
	InputHandler(EventListener *e) 
	{ 
		m_eventListener = e; 
		ControllerInit();
	};

	void ControllerInit();
	void handleInput(SDL_Event &e);

private:
	EventListener *m_eventListener;
	#define MAX_CONTROLLERS 1
	SDL_GameController *gameController[MAX_CONTROLLERS];
	int MaxJoysticks;
	int ControllerIndex;

};