#include "InstanceManager.h"


InstanceManager::InstanceManager(SystemManager * sm, StateManager * s, ResourceManager *rm, EventListener *listener, AStar * aStar, std::vector<Entity*> entities)
{
	m_listener = listener;
	m_stateManager = s;

	m_aStar = aStar;

	systemManager = sm;

	m_players = entities;

	townInstance = new TownInstance(sm, listener);
	shopInstance = new ShopInstance(sm, listener);

	worldMap = new WorldMap(sm, s, listener);
	battleMap = new BattleMap(sm, s, listener);
	dungeonMap = new DungeonMap(sm, s, rm, listener, aStar);
	gameOverInstance = new GameOverInstance(sm, s);

	menu = new MenuInstance(sm, listener, s, entities);
	options = new OptionsInstance(sm, listener, s);

	m_musicBox = new Entity("MusicBox");
	musicStuff = new MusicComponent("Overworld3", "play", true, 99999999, 100);
	m_musicBox->AddComponent(musicStuff);
	systemManager->soundSystem->AddEntity(m_musicBox);

	Generate("Menu");
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
	//else if (startInstance->Active())
	//{
	//	startInstance->Update();
	//}
	else if (townInstance->Active())
	{
		townInstance->Update();
	}
	else if (shopInstance->Active())
	{
		shopInstance->Update(m_players);
	}
	else if (menu->Active())
	{
		menu->Update();
	}
	else if (options->Active())
	{
		options->Update();
	}
	else if (gameOverInstance->Active())
	{
		gameOverInstance->Update(deltaTime);
	}
	else
	{
		battleMap->Update(deltaTime);
		m_aStar->setCurrentMapType("Battle");
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

	if (m_listener->MenuToWorld)
	{
		Reset();
		worldMap->Generate(25, 25, 100);
		worldMap->Load();
		worldMap->Active(true);
		menu->Active(false);
		m_listener->MenuToWorld = false;
	}
	else if (m_listener->MenuToOptions)
	{
		Reset();
		options->Load();
		options->Active(true);
		menu->Active(false);
		m_listener->MenuToOptions = false;
	}
	else if (m_listener->OptionsToMenu)
	{
		Reset();
		menu->Load();
		menu->Active(true);
		options->Active(false);
		m_listener->OptionsToMenu = false;
	}

	if (m_listener->TownToShop == true)
	{
		Reset();
		shopInstance->Generate(1);
		shopInstance->Active(true);
		townInstance->Active(false);
		worldMap->Active(false);
		m_listener->TownToShop = false;
	}
	else if (m_listener->ShopToTown == true)
	{
		Reset();
		Generate("Town");
		townInstance->Generate("j");
		townInstance->Active(true);
		shopInstance->Active(false);
		m_listener->ShopToTown = false;
	}

	if ((m_listener->host == true && m_listener->connected == true) || (m_listener->host == false && m_listener->connected == false))
	{
		if (m_stateManager->StartGame)
		{
			Reset();
			Generate("World");
			//startInstance->Active(false);
			worldMap->Active(true);
			m_stateManager->StartGame = false;
		}
		else if (m_listener->WorldToDungeon == true)
		{
			Reset();
			Generate("Dungeon");
			worldMap->Active(false);
			dungeonMap->Active(true);
			m_listener->WorldToDungeon = false;
		}
		else if (m_listener->WorldToEncounter == true)
		{
			Reset();
			Generate("Battle");
			worldMap->Active(false);
			battleMap->Active(true);
			m_listener->WorldToEncounter = false;
		}
		else if (m_listener->DungeonToWorld == true)
		{
			Reset();
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
		else if (m_stateManager->GameOver)
		{
			Generate("GameOver");
			gameOverInstance->Active(true);
			m_stateManager->GameOver = false;
		}
		else if (m_listener->WorldToTown == true)
		{
			Reset();
			systemManager->soundSystem->FullClear();
			musicStuff->setActive(false);
			musicStuff->setIdentifier("Town1");
			musicStuff->setPlay();
			systemManager->soundSystem->AddEntity(m_musicBox);
			Generate("Town");
			townInstance->Generate("j");
			townInstance->Active(true);
			worldMap->Active(false);
			m_listener->WorldToTown = false;
			m_listener->ToTown = true;
		}
		else if (m_listener->TownToWorld == true)
		{
			Reset();
			systemManager->soundSystem->FullClear();
			musicStuff->setActive(false);
			musicStuff->setIdentifier("Overworld3");
			musicStuff->setPlay();
			systemManager->soundSystem->AddEntity(m_musicBox);
			worldMap->Load();
			worldMap->Active(true);
			townInstance->Active(false);
			m_listener->TownToWorld = false;
			m_listener->ToWorldMap = true;
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
	else if (instanceID == "Menu")
	{
		menu->Active(false);
		options->Active(false);
		menu->Load();
		menu->Active(true);
	}
	else if (instanceID == "GameOver")
	{
		gameOverInstance->Generate();
	}
	else if (instanceID == "Town")
	{
		townInstance->Generate("jimmie");
	}
}

void InstanceManager::GenerateFromServer()
{
	if (m_listener->ToDungeon1 == true)
	{
		Reset();
		dungeonMap->Generate("DungeonMap1");
		worldMap->Active(false);
		dungeonMap->Active(true);
		m_listener->ToDungeon1 = false;
	}
	else if (m_listener->ToDungeon2 == true)
	{
		Reset();
		dungeonMap->Generate("DungeonMap2");
		worldMap->Active(false);
		dungeonMap->Active(true);
		m_listener->ToDungeon2 = false;
	}
	else if (m_listener->ToDungeon3 == true)
	{
		Reset();
		dungeonMap->Generate("DungeonMap3");
		worldMap->Active(false);
		dungeonMap->Active(true);
		m_listener->ToDungeon3 = false;
	}
	else if (m_listener->ToDungeon4 == true)
	{
		Reset();
		dungeonMap->Generate("DungeonMap4");
		worldMap->Active(false);
		dungeonMap->Active(true);
		m_listener->ToDungeon4 = false;
	}
	else if (m_listener->ToDungeon5 == true)
	{
		Reset();
		dungeonMap->Generate("DungeonMap5");
		worldMap->Active(false);
		dungeonMap->Active(true);
		m_listener->ToDungeon5 = false;
	}
	else if (m_listener->ToWorldMap == true)
	{
		m_listener->TownToWorld = false;
		Reset();
		systemManager->soundSystem->FullClear();
		musicStuff->setActive(false);
		musicStuff->setIdentifier("Overworld3");
		musicStuff->setPlay();
		systemManager->soundSystem->AddEntity(m_musicBox);
		worldMap->Load();
		worldMap->Active(true);
		dungeonMap->Active(false);
		battleMap->Active(false);
		townInstance->Active(false);
		m_listener->ToWorldMap = false;
	}
	else if (m_listener->ToTown == true)
	{
		Reset();
		systemManager->soundSystem->FullClear();
		musicStuff->setActive(false);
		musicStuff->setIdentifier("Town1");
		musicStuff->setPlay();
		systemManager->soundSystem->AddEntity(m_musicBox);
		Generate("Town");
		townInstance->Generate("j");
		townInstance->Active(true);
		worldMap->Active(false);
		m_listener->ToTown = false;
	}
}

void InstanceManager::Reset()
{
	systemManager->MassSelectiveClear();
}