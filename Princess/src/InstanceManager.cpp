#include "InstanceManager.h"

InstanceManager::InstanceManager(SystemManager * sm, StateManager * s, ResourceManager *rm, EventListener *listener)
{
	m_listener = listener;
	m_stateManager = s;

	worldMap = new WorldMap(sm, s, listener);
	battleMap = new BattleMap(sm, s, listener);
	dungeonMap = new DungeonMap(sm, s, rm, listener);
	//startInstance = new StartInstance(sm, s);

	Generate("World");
}

void InstanceManager::Update(float deltaTime)
{
	if (worldMap->Active())
	{
		worldMap->Update();
	}
	else if (dungeonMap->Active())
	{
		dungeonMap->Update(deltaTime);
	}
	//else if(startInstance->Active())
	//{
	//	startInstance->Update();
	//}
	else
	{
		battleMap->Update(deltaTime);
	}

	//if (m_stateManager->StartGame)
	//{
	//	Generate("World");
	//	startInstance->Active(false);
	//	worldMap->Active(true);
	//	m_stateManager->StartGame = false;
	//}
	if ((m_listener->host == true && m_listener->connected == true) || (m_listener->host == false && m_listener->connected == false))
	{
		if (m_listener->WorldToDungeon == true)
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

	else if (m_listener->host == false && m_listener->connected == true)
	{
		GenerateFromServer();
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
	//else if (instanceID == "Start")
	//{
	//	startInstance->Generate();
	//}
}

void InstanceManager::GenerateFromServer()
{
	if (m_listener->ToDungeon1 == true)
	{
		dungeonMap->Generate("DungeonMap1");
		worldMap->Active(false);
		dungeonMap->Active(true);
		m_listener->ToDungeon1 = false;
	}
	else if (m_listener->ToDungeon2 == true)
	{
		dungeonMap->Generate("DungeonMap2");
		worldMap->Active(false);
		dungeonMap->Active(true);
		m_listener->ToDungeon2 = false;
	}
	else if (m_listener->ToDungeon3 == true)
	{
		dungeonMap->Generate("DungeonMap3");
		worldMap->Active(false);
		dungeonMap->Active(true);
		m_listener->ToDungeon3 = false;
	}
	else if (m_listener->ToDungeon4 == true)
	{
		dungeonMap->Generate("DungeonMap4");
		worldMap->Active(false);
		dungeonMap->Active(true);
		m_listener->ToDungeon4 = false;
	}
	else if (m_listener->ToDungeon5 == true)
	{
		dungeonMap->Generate("DungeonMap5");
		worldMap->Active(false);
		dungeonMap->Active(true);
		m_listener->ToDungeon5 = false;
	}
	else if (m_listener->ToWorldMap == true)
	{
		worldMap->Load();
		worldMap->Active(true);
		dungeonMap->Active(false);
		battleMap->Active(false);
		m_listener->ToWorldMap = false;
	}
}