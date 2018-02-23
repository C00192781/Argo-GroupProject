
#pragma once

#include "WorldMap.h"
#include "BattleMap.h"
#include "DungeonMap.h"
#include "TownInstance.h"
#include "EventListener.h"
#include "StartInstance.h"
#include "MenuInstance.h"
#include "OptionsInstance.h"
#include "ShopInstance.h"
#include <vector>

class InstanceManager
{
public:

	InstanceManager(SystemManager * sm, StateManager * s, ResourceManager *rm, EventListener *listener, std::vector<Entity*> entities);

	WorldMap *worldMap;
	BattleMap* battleMap;
	DungeonMap* dungeonMap;
	StartInstance* startInstance;
	TownInstance* townInstance;
	ShopInstance* shopInstance;
	SystemManager* systemManager;
	MenuInstance* menu;
	OptionsInstance* options;

	void Update(float deltaTime);
	void Generate(string instanceID);
	void Reset();
private:
	EventListener *m_listener;
	StateManager *m_stateManager;

	std::vector<Entity*> m_players;
	Entity * m_musicBox;
	MusicComponent * musicStuff;

};