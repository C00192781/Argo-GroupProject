#pragma once

#include "Instance.h"
#include "DungeonTileFactory.h"
#include "BasicEnemy.h"
#include "Pickup.h"
class DungeonMap : public Instance
{
public:
	DungeonMap(SystemManager * sm, StateManager * s, ResourceManager *rm, EventListener *listener, AStar *aStar);
	~DungeonMap();

	void Update() {}
	void Update(float deltaTime);
	void Render() {};

	void Generate();
	void Generate(std::string mapName);
private:
	ResourceManager * m_resourceManager;
	EventListener *m_listener;
	SDL_Point m_startPoint;
	std::vector<Entity*> m_enemies; // points to the enemies in collision system
	std::vector<Entity*> m_pickups; // points to the pickups in collision system
	float m_timeRemaining;
	AStar * m_aStar;
};