#pragma once

#include "System.h"
#include "ControlComponent.h"

class ControlSystem : public System
{
public:
	ControlSystem() {}

	void Update() {}
	void Update(SDL_Event *e);
};