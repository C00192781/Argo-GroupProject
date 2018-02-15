#include "InstanceManager.h"

InstanceManager::InstanceManager(SystemManager * sm, StateManager * s, ResourceManager *rm)
{
	worldMap = new WorldMap(sm, s);
	battleMap = new BattleMap(sm, s);
	dungeonMap = new DungeonMap(sm, s, rm);

	//dungeonMap->generate();
}

void InstanceManager::Update(float deltaTime)
{
	if (dungeonMap->Active())
	{
		dungeonMap->Update(deltaTime);
	}
}

void InstanceManager::Generate(std::string instanceID)
{
	if (instanceID == "World")
	{
		worldMap->Generate(25, 25, 100);
	}
	else if (instanceID == "Dungeon")
	{
		dungeonMap->Generate();
	}
	else if (instanceID == "Battle")
	{
		battleMap->Generate("");
	}
	else
	{
		
	}
}