#include "InstanceManager.h"

InstanceManager::InstanceManager(SystemManager * sm, StateManager * s, ResourceManager *rm, EventListener *listener)
{
	m_listener = listener;
	m_stateManager = s;

	auto temp = new TownInstance(sm);
	townInstance.push_back(temp);
	//townInstance->push_back( new TownInstance(sm));

	worldMap = new WorldMap(sm, s, listener);
	battleMap = new BattleMap(sm, s, listener);
	dungeonMap = new DungeonMap(sm, s, rm, listener);
	startInstance = new StartInstance(sm, s);

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
	else if (startInstance->Active())
	{
		startInstance->Update();
	}
	else if (townInstance.at(0)->Active())
	{
		townInstance.at(0)->Update();
	}
	else
	{
		battleMap->Update(deltaTime);
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
	else if (m_listener->WorldToTown == true)
	{
		Generate("Town");
		townInstance.at(0)->Load();
		townInstance.at(0)->Active(true);
		worldMap->Active(false);
		m_listener->WorldToTown = false;
	}
	else if (m_listener->TownToWorld == true)
	{
		worldMap->Load();
		worldMap->Active(true);
		townInstance.at(0)->Active(false);
		m_listener->TownToWorld = false;
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
	else if (instanceID == "Town")
	{

		townInstance.at(0)->Generate("jimmie");

		//TownInstance t = TownInstance(&systemManager);
		//t.Generate("jimmie");
	}
}