#include "InstanceManager.h"

InstanceManager::InstanceManager(SystemManager * sm, StateManager * s, ResourceManager *rm, EventListener *listener)
{
	m_listener = listener;
	m_stateManager = s;

	worldMap = new WorldMap(sm, s, listener);
	battleMap = new BattleMap(sm, s, listener);
	dungeonMap = new DungeonMap(sm, s, rm, listener);
	startInstance = new StartInstance(sm, s);
	gameOverInstance = new GameOverInstance(sm, s);

	Generate("Start");
	startInstance->Active(true);
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
	else if(startInstance->Active())
	{
		startInstance->Update();
	}
	else if (battleMap->Active())
	{
		battleMap->Update(deltaTime);
	}
	if (gameOverInstance->Active())
	{
		gameOverInstance->Update(deltaTime);
	}

	if (m_stateManager->ReturnToWorld)
	{
		if (battleMap->Active())
		{
			m_listener->EncounterToWorld = true;
		}
		else if (dungeonMap->Active())
		{
			m_listener->DungeonToWorld = true;
		}
		gameOverInstance->Active(false);
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
		m_stateManager->SaveGame = true;
	}
	else if (m_listener->WorldToEncounter == true)
	{
		Generate("Battle");
		worldMap->Active(false);
		battleMap->Active(true);
		m_listener->WorldToEncounter = false;
		m_stateManager->SaveGame = true;
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
	else if(m_stateManager->GameOver)
	{
		Generate("GameOver");
		gameOverInstance->Active(true);
		m_stateManager->GameOver = false;
	}
	if (m_stateManager->ReturnToWorld)
	{
		m_stateManager->ReturnToWorld = false;
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
	else if (instanceID == "GameOver")
	{
		gameOverInstance->Generate();
	}
}