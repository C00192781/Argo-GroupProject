#pragma once

#include "System.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"

class MovementSystem : public System
{
public:
	MovementSystem() 
	{
		m_entities.push_back(new Entity("Null"));
		delete m_entities.back();
		m_entities.clear();
	}

	void Update() {}
	void Update(float deltaTime);
	void LoadComponent();
	void UnloadComponent(int x);
private:
	int m_mouseX;
	int m_mouseY;
};