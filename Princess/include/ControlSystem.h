#pragma once

#include "System.h"
#include "ControlComponent.h"
#include "MovementComponent.h"
#include "ProjectileComponent.h"
#include "SpriteComponent.h"
#include "CollisionSystem.h"
#include "MovementComponent.h"


class ControlSystem : public System
{
public:
	ControlSystem(EventListener *e) 
	{ 
		m_eventListener = e; 
	};

	void Update();
	void getSystemEntities(std::vector<Entity*>* projectiles) { m_projectiles = projectiles; }
private:

	EventListener *m_eventListener;
	std::vector<Entity*>* m_projectiles;
};