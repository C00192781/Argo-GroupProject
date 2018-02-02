#pragma once

#include "System.h"
#include "PositionComponent.h"
#include "MovementComponent.h"

class MovementSystem : public System
{
public:
	MovementSystem() {}

	void Update() {}
	void Update(float deltaTime);
};