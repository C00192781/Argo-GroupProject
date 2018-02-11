#pragma once

#include "System.h"
#include "PositionComponent.h"
#include "MovementComponent.h"

class MovementSystem : public System
{
public:
	MovementSystem() {}

	void Update();

private:
	void LoadComponent() {};
	void UnloadComponent(int x) {};
};