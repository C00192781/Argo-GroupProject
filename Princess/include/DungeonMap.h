#pragma once

#include "Instance.h"
#include "DungeonTileFactory.h"

class DungeonMap : public Instance
{
public:
	DungeonMap(SystemManager * sm, StateManager * s, ResourceManager *rm);
	~DungeonMap();

	void Update() {}
	void Update(float deltaTime);
	void Render() {};

	void Generate();
private:
	ResourceManager * m_resourceManager;
	std::vector<Entity*> m_enemies; // points to the enemies in collision system
	float m_timeRemaining;
};