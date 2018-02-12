#pragma once

#include "System.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include <vector>

class MovementSystem : public System
{
public:
	MovementSystem() {}
	MovementSystem(int windowWidth, int windowHeight)
	{
		m_windowWidth = windowWidth;
		m_windowHeight = windowHeight;
	}

	void Update() {}
	void Update(float deltaTime);
private:
	void LoadComponent();
	void UnloadComponent(int x);

	int m_mouseX;
	int m_mouseY;

	int m_windowWidth;
	int m_windowHeight;

	std::vector<PositionComponent*> m_positionComponent;
	std::vector<MovementComponent*> m_movementComponent;
	std::vector<CollisionComponent*> m_collisionComponent;
};