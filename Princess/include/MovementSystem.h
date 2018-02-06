#pragma once

#include "System.h"
#include "RectangleComponent.h"
#include "MovementComponent.h"

class MovementSystem : public System
{
public:
	MovementSystem() {}

	void Update();
private:
	SDL_Point* position;
	SDL_Point* velocity;
};