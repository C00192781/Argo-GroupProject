
#pragma once

#include "WorldMap.h"
#include "BattleMap.h"
#include "DungeonMap.h"
#include "TownInstance.h"
#include "EventListener.h"
#include "StartInstance.h"
#include <vector>

class InstanceManager
{
public:

	InstanceManager(SystemManager * sm, StateManager * s, ResourceManager *rm, EventListener *listener);

	WorldMap *worldMap;
	BattleMap* battleMap;
	DungeonMap* dungeonMap;
	StartInstance* startInstance;
	std::vector<TownInstance*> townInstance;

	void Update(float deltaTime);

	void Generate(string instanceID);

	void GenerateFromServer();
private:
	EventListener *m_listener;
	StateManager *m_stateManager;
};