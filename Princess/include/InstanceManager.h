
#pragma once

#include "WorldMap.h"
#include "BattleMap.h"
#include "DungeonMap.h"
#include "TownInstance.h"
#include "EventListener.h"
#include "StartInstance.h"
#include "GameOverInstance.h"
#include "MenuInstance.h"
#include "OptionsInstance.h"
#include "ShopInstance.h"
#include "SystemManager.h"
#include <vector>

class InstanceManager
{
public:

	InstanceManager(SystemManager * sm, StateManager * s, ResourceManager *rm, EventListener *listener, AStar * aStar, std::vector<Entity*> entities);

	WorldMap *worldMap;
	BattleMap* battleMap;
	DungeonMap* dungeonMap;
	GameOverInstance* gameOverInstance;
	TownInstance* townInstance;
	ShopInstance* shopInstance;
	SystemManager* systemManager;
	MenuInstance* menu;
	OptionsInstance* options;

	void Update(float deltaTime);
	void Generate(string instanceID);
	void GenerateFromServer();
	void Reset();
private:
	EventListener *m_listener;
	StateManager *m_stateManager;

	AStar *m_aStar;

	std::vector<Entity*> m_players;
	Entity * m_musicBox;
	MusicComponent * musicStuff;

};