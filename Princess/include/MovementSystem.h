#pragma once

#include "System.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include <vector>
#include "SpriteComponent.h"
#include "EventListener.h"

class MovementSystem : public System
{
public:
	MovementSystem() { m_rollEnd = true; }

	MovementSystem(int windowWidth, int windowHeight, EventListener *e)
	{
		m_windowWidth = windowWidth;
		m_windowHeight = windowHeight;
		m_eventListener = e;
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
	std::vector<bool>  m_rollAnim;

	int m_lastXVel;
	int m_lastYVel;
	bool m_rollEnd = true;

	std::vector<Entity*> m_playerEnts;

	int countedFrames[4] = { 0,0,0,0 };
	int cooldownFrames[4] = { 0,0,0,0 };

	std::vector<PositionComponent*> m_positionComponent;
	std::vector<MovementComponent*> m_movementComponent;
	std::vector<CollisionComponent*> m_collisionComponent;

	EventListener *m_eventListener;
};