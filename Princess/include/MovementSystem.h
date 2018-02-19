#pragma once

#include "System.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include <vector>
#include "SpriteComponent.h"
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
	int countedFrames;
	int cooldownFrames;
	int m_windowWidth;
	int m_windowHeight;
	bool m_rollAnim;
	int m_lastXVel;
	int m_lastYVel;
};