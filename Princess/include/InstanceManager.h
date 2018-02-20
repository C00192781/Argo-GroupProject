#pragma once

#include "WorldMap.h"
#include "BattleMap.h"
#include "DungeonMap.h"
#include "TownInstance.h"
#include "EventListener.h"
#include <vector>

class InstanceManager
{
public:
	InstanceManager(SystemManager * sm, StateManager * s, ResourceManager *rm, EventListener *listener);

	WorldMap *worldMap;
	BattleMap* battleMap;
	DungeonMap* dungeonMap;
	std::vector<TownInstance*> townInstance;

	void Update(float deltaTime);

	void Generate(string instanceID);
private:
	EventListener *m_listener;
};