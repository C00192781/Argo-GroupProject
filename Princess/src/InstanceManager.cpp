#include "InstanceManager.h"

InstanceManager::InstanceManager(SystemManager * sm, StateManager * s, ResourceManager *rm, EventListener *listener, AStar * aStar)
{
	m_listener = listener;
	m_stateManager = s;

	m_aStar = aStar;
	worldMap = new WorldMap(sm, s, listener);
	battleMap = new BattleMap(sm, s, listener);
	dungeonMap = new DungeonMap(sm, s, rm, listener, aStar);
	startInstance = new StartInstance(sm, s);

	Generate("World");
}

void InstanceManager::Update(float deltaTime)
{
	if (worldMap->Active())
	{
		worldMap->Update();
		m_aStar->setCurrentMapType("World");
	}
	else if (dungeonMap->Active())
	{
		dungeonMap->Update(deltaTime);
		m_aStar->setCurrentMapType("Dungeon");
	}
	else if(startInstance->Active())
	{
		startInstance->Update();
	}
	else
	{
		battleMap->Update(deltaTime);
		m_aStar->setCurrentMapType("Battle");
	}

	if (m_stateManager->StartGame)
	{
		Generate("World");
		startInstance->Active(false);
		worldMap->Active(true);
		m_stateManager->StartGame = false;
	}
	else if (m_listener->WorldToDungeon == true)
	{
		Generate("Dungeon");
		worldMap->Active(false);
		dungeonMap->Active(true);
		m_listener->WorldToDungeon = false;
	}
	else if (m_listener->WorldToEncounter == true)
	{
		Generate("Battle");
		worldMap->Active(false);
		battleMap->Active(true);
		m_listener->WorldToEncounter = false;
	}
	else if (m_listener->DungeonToWorld == true)
	{
		worldMap->Load();
		worldMap->Active(true);
		dungeonMap->Active(false);
		m_listener->DungeonToWorld = false;
	}
	else if (m_listener->EncounterToWorld == true)
	{
		worldMap->Load();
		worldMap->Active(true);
		battleMap->Active(false);
		m_listener->EncounterToWorld = false;
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
	else if (instanceID == "Start")
	{
		startInstance->Generate();
	}
}