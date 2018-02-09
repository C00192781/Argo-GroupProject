#pragma once

#include "System.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"

class MovementSystem : public System
{
public:
	MovementSystem() {}

	void Update() {}
	void Update(float deltaTime);
private:
	int m_mouseX;
	int m_mouseY;
}; 