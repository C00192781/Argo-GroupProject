#include "DungeonMap.h"

DungeonMap::DungeonMap(SystemManager * sm, StateManager * s, ResourceManager * rm)
{
	m_systemManager = sm;
	m_stateManager = s;
	m_resourceManager = rm;

	m_resourceManager->AddMap("DungeonMap1", "DungeonMap1.json");
	m_resourceManager->AddMap("DungeonMap2", "DungeonMap2.json");
	m_resourceManager->AddMap("DungeonMap3", "DungeonMap3.json");
	m_resourceManager->AddMap("DungeonMap4", "DungeonMap4.json");
	m_resourceManager->AddMap("DungeonMap5", "DungeonMap5.json");
	m_resourceManager->AddMap("SafeArea", "SafeArea.json");

	m_resourceManager->AddTexture("DungeonTiles", "Dungeon_Tiles.png");
	m_timeRemaining = 5;
}

void DungeonMap::Generate()
{
	m_active = true;

	for (int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities.at(i);
	}
	m_entities.clear();
	m_entities.shrink_to_fit();
	m_systemManager->controlSystem->SelectiveClear();
	m_systemManager->renderSystem->SelectiveClear();
	m_systemManager->movementSystem->SelectiveClear();
	m_systemManager->collisionSystem->SelectiveClear();

	//int randomMapNumber = rand() % 5;
	int randomMapNumber = 0;
	std::string mapName;

	if (randomMapNumber == 0)
	{
		mapName = "DungeonMap1";
	}
	else if (randomMapNumber == 1)
	{
		mapName = "DungeonMap2";
	}
	else if (randomMapNumber == 2)
	{
		mapName = "DungeonMap3";
	}
	else if (randomMapNumber == 3)
	{
		mapName = "DungeonMap4";
	}
	else
	{
		mapName = "DungeonMap5";
	}

	DungeonTileFactory factory;

	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			if (m_resourceManager->GetMapElement(mapName, i, j) == "W")
			{
				m_entities.push_back(factory.Wall("DungeonTiles", j, i, m_systemManager->renderSystem->GetScale()));
				m_systemManager->collisionSystem->AddEntity(m_entities.back());
			}
			else if (m_resourceManager->GetMapElement(mapName, i, j) == "F")
			{
				m_entities.push_back(factory.Floor("DungeonTiles", j, i, m_systemManager->renderSystem->GetScale()));
			}
			else if (m_resourceManager->GetMapElement(mapName, i, j) == "B")
			{
				m_entities.push_back(factory.Grass("DungeonTiles", j, i, m_systemManager->renderSystem->GetScale()));
			}
			m_systemManager->renderSystem->AddEntity(m_entities.back());
		}
	}

	m_systemManager->collisionSystem->updateBounds(SDL_Rect{0, 0, 16 * 24 * (int)m_systemManager->renderSystem->GetScale(), 16 * 24 * (int)m_systemManager->renderSystem->GetScale() });
}

void DungeonMap::Update(float deltaTime)
{
	if (m_enemies.empty())
	{
		m_timeRemaining -= deltaTime;

		if (m_timeRemaining <= 0)
		{
			m_active = false;
		}
	}
}