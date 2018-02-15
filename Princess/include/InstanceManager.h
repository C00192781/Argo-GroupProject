#pragma once

#include "WorldMap.h"
#include "BattleMap.h"
#include "DungeonMap.h"
#include "TownInstance.h"
#include <vector>

class InstanceManager
{
public:
	InstanceManager(SystemManager * sm, StateManager * s, ResourceManager *rm);

	WorldMap *worldMap;
	BattleMap* battleMap;
	DungeonMap* dungeonMap;
	std::vector<TownInstance*> townInstance;

	void Update(float deltaTime);

	void Generate(string instanceID);
};