#pragma once

#include "System.h"
#include "ControlComponent.h"
#include "MovementComponent.h"
#include "ProjectileComponent.h"
#include "WeaponComponent.h"
#include "SpriteComponent.h"
#include "CollisionSystem.h"
#include "AttributesComponent.h"

class ControlSystem : public System
{
public:
	ControlSystem(EventListener *e)
	{
		m_eventListener = e;
		lastTickTime = 0.0f;
		delta = 0.0f;
		tickTime = 0.0f;
		shoot = false;
		playerPos = SDL_Point{ 0,0 };
		x = 0.0f;
		y = 0.0f;
		m_entities.push_back(new Entity("Null"));
		delete m_entities.back();
		m_entities.clear();
		totalPlayerMovement = 0;
	};
	void LoadComponent() {};
	void UnloadComponent(int x) {};
	void Update();
	void getSystemEntities(std::vector<Entity*>* projectiles) { m_projectiles = projectiles; }
	float getTotalPlayerMovement() { return totalPlayerMovement; }
	int index = 0;
private:

	EventListener *m_eventListener;
	std::vector<Entity*>* m_projectiles;

	uint32_t lastTickTime, delta, tickTime;
	bool shoot;
	SDL_Point playerPos;
	int x, y;
	float totalPlayerMovement;
};
	
