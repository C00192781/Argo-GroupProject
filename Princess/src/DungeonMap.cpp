#include "DungeonMap.h"

DungeonMap::DungeonMap(SystemManager * sm, StateManager * s, ResourceManager * rm)
{
	m_systemManager = sm;
	m_stateManager = s;
	m_resourceManager = rm;

	m_resourceManager->AddMap("DungeonMap1", "DungeonMap1.json");

	m_resourceManager->AddTexture("DungeonTiles", "Dungeon_Tiles.png");
}

void DungeonMap::generate()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities.at(i);
	}
	m_entities.clear();
	m_entities.shrink_to_fit();
	m_systemManager->controlSystem->SelectiveClear();
	m_systemManager->renderSystem->SelectiveClear();
	m_systemManager->movementSystem->SelectiveClear();

	int randomMapNumber = rand() % 5;
	randomMapNumber = 0; // ****REMOVE THIS LATER****
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
			if (m_resourceManager->GetMapElement(mapName, i, j) == "T")
			{
				m_entities.push_back(factory.WallTop("DungeonTiles", j, i));
			}
			else if (m_resourceManager->GetMapElement(mapName, j, i) == "W")
			{
				m_entities.push_back(factory.Wall("DungeonTiles", j, i));
			}
			else if (m_resourceManager->GetMapElement(mapName, i, j) == "F")
			{
				m_entities.push_back(factory.Floor("DungeonTiles", j, i));
			}
			else if (m_resourceManager->GetMapElement(mapName, i, j) == "B")
			{
				m_entities.push_back(factory.Grass("DungeonTiles", j, i));
			}
			m_systemManager->renderSystem->AddEntity(m_entities.back());
		}
	}

	std::cout << "DONE" << std::endl;
}