#include "WorldMap.h"

WorldMap::WorldMap(SystemManager * sm, StateManager * s, EventListener* listener)
{
	m_systemManager = sm;
	m_stateManager = s;
	m_listener = listener;
}

WorldMap::~WorldMap()
{
}

void WorldMap::Generate(int width, int height, int chaosFactor)
{
	m_active = true;
	m_systemManager->healthSystem->Active(false);

	Entity* player2 = m_systemManager->collisionSystem->FindEntity("Player", 2); //discern between players
	Entity* player3 = m_systemManager->collisionSystem->FindEntity("Player", 1); //discern between players
	Entity* player4 = m_systemManager->collisionSystem->FindEntity("Player", 0); //discern between players
	player2->Active(false);
	player3->Active(false);
	player4->Active(false);

	for (int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities.at(i);
	}
	m_entities.clear();
	m_entities.shrink_to_fit();
	m_systemManager->controlSystem->SelectiveClear();
	m_systemManager->renderSystem->SelectiveClear();
	m_systemManager->movementSystem->SelectiveClear();
	m_systemManager->healthSystem->SelectiveClear();

	WorldTileFactory factory;

	std::vector<std::vector<std::string>> mapHolder;

	//Creates Water
	for (int i = 0; i < width + 12; i++)
	{
		std::vector<std::string> holder;
		for (int j = 0; j < height + 12; j++)
		{
			holder.push_back("DeepWater");
		}
		mapHolder.push_back(holder);
	}

	//Creates the Beaches
	for (int i = 0; i < width + 12; i++)
	{
		for (int j = 0; j < height + 12; j++)
		{
			if (i > 5 && i < width + 6 && j > 5 && j < height + 6)
			{
				if (i == 6 || i == width + 5 || j == 6 || j == height + 5)
				{
					ApplyLake(&mapHolder, i, j, (rand() % 4) + 2);
				}
				else if (i == 7 || i == width + 4 || j == 7 || j == height + 4)
				{
					mapHolder.at(i).at(j) = "Desert";
				}
				else
				{
					mapHolder.at(i).at(j) = "Planes";
				}
			}
		}
	}
	int holder = (rand() % 6) + 2;
	for (int i = 0; i < holder; i++)
	{
		ApplyLake(&mapHolder, (rand() % ((width + 12) - 14)) + 7, (rand() % ((height + 12) - 14)) + 7, (rand() % 4) + 2);
	}
	holder = (rand() % 5) + 4;
	for (int i = 0; i < holder; i++)
	{
		ApplySnowField(&mapHolder, (rand() % ((width + 12) - 14)) + 7, (rand() % ((height + 12) - 14)) + 7, (rand() % 2) + 4);
	}
	holder = (rand() % 5) + 4;
	for (int i = 0; i < holder; i++)
	{
		ApplyDesert(&mapHolder, (rand() % ((width + 12) - 14)) + 7, (rand() % ((height + 12) - 14)) + 7, (rand() % 2) + 4);
	}
	holder = (rand() % chaosFactor) + 2;
	for (int i = 0; i < holder; i++)
	{
		ApplyForest(&mapHolder, (rand() % ((width + 12) - 14)) + 7, (rand() % ((height + 12) - 14)) + 7, (rand() % 2) + 2);
	}
	holder = (rand() % chaosFactor) + 2;
	for (int i = 0; i < holder; i++)
	{
		ApplyMeadow(&mapHolder, (rand() % ((width + 12) - 14)) + 7, (rand() % ((height + 12) - 14)) + 7, (rand() % 2) + 2);
	}
	holder = (rand() % chaosFactor) + 2;
	for (int i = 0; i < holder; i++)
	{
		ApplyDune(&mapHolder, (rand() % ((width + 12) - 14)) + 7, (rand() % ((height + 12) - 14)) + 7, (rand() % 2) + 2);
	}
	holder = (rand() % chaosFactor) + 2;
	for (int i = 0; i < holder; i++)
	{
		ApplyRock(&mapHolder, (rand() % ((width + 12) - 14)) + 7, (rand() % ((height + 12) - 14)) + 7, (rand() % 2) + 2);
	}
	holder = (rand() % chaosFactor) + 2;
	for (int i = 0; i < holder; i++)
	{
		ApplySnowDune(&mapHolder, (rand() % ((width + 12) - 14)) + 7, (rand() % ((height + 12) - 14)) + 7, (rand() % 2) + 2);
	}
	holder = (rand() % chaosFactor) + 2;
	for (int i = 0; i < holder; i++)
	{
		ApplyGlacier(&mapHolder, (rand() % ((width + 12) - 14)) + 7, (rand() % ((height + 12) - 14)) + 7, (rand() % 2) + 2);
	}
	for (int i = 0; i < width + 12; i++)
	{
		for (int j = 0; j < height + 12; j++)
		{
			if (mapHolder.at(i).at(j) == "Water")
			{
				m_entities.push_back(factory.Water("WorldTurf", i * (16 * m_systemManager->renderSystem->GetScale()), j * (16 * m_systemManager->renderSystem->GetScale())));
			}
			else if (mapHolder.at(i).at(j) == "Desert")
			{
				m_entities.push_back(factory.Desert("WorldTurf", i * (16 * m_systemManager->renderSystem->GetScale()), j * (16 * m_systemManager->renderSystem->GetScale())));
			}
			else if (mapHolder.at(i).at(j) == "Planes")
			{
				m_entities.push_back(factory.Planes("WorldTurf", i * (16 * m_systemManager->renderSystem->GetScale()), j * (16 * m_systemManager->renderSystem->GetScale())));
			}
			else if (mapHolder.at(i).at(j) == "SnowField")
			{
				m_entities.push_back(factory.SnowField("WorldTurf", i * (16 * m_systemManager->renderSystem->GetScale()), j * (16 * m_systemManager->renderSystem->GetScale())));
			}
			else if (mapHolder.at(i).at(j) == "Forest")
			{
				m_entities.push_back(factory.Forest("WorldTurf", i * (16 * m_systemManager->renderSystem->GetScale()), j * (16 * m_systemManager->renderSystem->GetScale())));
			}
			else if (mapHolder.at(i).at(j) == "Meadow")
			{
				m_entities.push_back(factory.Meadow("WorldTurf", i * (16 * m_systemManager->renderSystem->GetScale()), j * (16 * m_systemManager->renderSystem->GetScale())));
			}
			else if (mapHolder.at(i).at(j) == "Dune")
			{
				m_entities.push_back(factory.Dunes("WorldTurf", i * (16 * m_systemManager->renderSystem->GetScale()), j * (16 * m_systemManager->renderSystem->GetScale())));
			}
			else if (mapHolder.at(i).at(j) == "SnowDune")
			{
				m_entities.push_back(factory.SnowDunes("WorldTurf", i * (16 * m_systemManager->renderSystem->GetScale()), j * (16 * m_systemManager->renderSystem->GetScale())));
			}
			else if (mapHolder.at(i).at(j) == "Rock")
			{
				m_entities.push_back(factory.Rock("WorldTurf", i * (16 * m_systemManager->renderSystem->GetScale()), j * (16 * m_systemManager->renderSystem->GetScale())));
			}
			else if (mapHolder.at(i).at(j) == "Glacier")
			{
				m_entities.push_back(factory.Glacier("WorldTurf", i * (16 * m_systemManager->renderSystem->GetScale()), j * (16 * m_systemManager->renderSystem->GetScale())));
			}
			else if (mapHolder.at(i).at(j) == "DeepWater")
			{
				m_entities.push_back(factory.DeepWater("WorldTurf", i * (16 * m_systemManager->renderSystem->GetScale()), j * (16 * m_systemManager->renderSystem->GetScale())));
			}
			m_systemManager->renderSystem->AddEntity(m_entities.back());
		}
	}
	bool done = false;
	int giveUp = 50;
	while (!done && giveUp > 0)
	{
		int xHolder = rand() % width;
		int yHolder = rand() % height;
		if (mapHolder.at(xHolder).at(yHolder) != "Water" && mapHolder.at(xHolder).at(yHolder) != "DeepWater" && mapHolder.at(xHolder).at(yHolder) != "Town" && mapHolder.at(xHolder).at(yHolder) != "Castle" && mapHolder.at(xHolder).at(yHolder) != "Dungeon" && mapHolder.at(xHolder).at(yHolder) != "DarkCastle")
		{
			mapHolder.at(xHolder).at(yHolder) = "Castle";
			m_entities.push_back(factory.Castle("WorldTurf", xHolder * (16 * m_systemManager->renderSystem->GetScale()), yHolder * (16 * m_systemManager->renderSystem->GetScale())));
			m_systemManager->renderSystem->AddEntity(m_entities.back());
			done = true;
		}
		giveUp--;
	}
	done = false;
	giveUp = 50;
	while (!done && giveUp > 0)
	{
		int xHolder = rand() % width;
		int yHolder = rand() % height;
		if (mapHolder.at(xHolder).at(yHolder) != "Water" && mapHolder.at(xHolder).at(yHolder) != "DeepWater" && mapHolder.at(xHolder).at(yHolder) != "Town" && mapHolder.at(xHolder).at(yHolder) != "Castle" && mapHolder.at(xHolder).at(yHolder) != "Dungeon" && mapHolder.at(xHolder).at(yHolder) != "DarkCastle")
		{
			mapHolder.at(xHolder).at(yHolder) = "DarkCastle";
			m_entities.push_back(factory.DarkCastle("WorldTurf", xHolder * (16 * m_systemManager->renderSystem->GetScale()), yHolder * (16 * m_systemManager->renderSystem->GetScale())));
			m_systemManager->renderSystem->AddEntity(m_entities.back());
			done = true;
		}
		giveUp--;
	}
	holder = (rand() % (chaosFactor / 4)) + 2;
	for (int i = 0; i < holder; i++)
	{
		bool done = false;
		int giveUp = 50;
		while (!done && giveUp > 0)
		{
			int xHolder = rand() % width;
			int yHolder = rand() % height;
			if (mapHolder.at(xHolder).at(yHolder) != "Water" && mapHolder.at(xHolder).at(yHolder) != "DeepWater" && mapHolder.at(xHolder).at(yHolder) != "Town" && mapHolder.at(xHolder).at(yHolder) != "Castle" && mapHolder.at(xHolder).at(yHolder) != "Dungeon" && mapHolder.at(xHolder).at(yHolder) != "DarkCastle")
			{
				mapHolder.at(xHolder).at(yHolder) = "Town";
				m_entities.push_back(factory.Town("WorldTurf", xHolder * (16 * m_systemManager->renderSystem->GetScale()), yHolder * (16 * m_systemManager->renderSystem->GetScale())));
				m_systemManager->renderSystem->AddEntity(m_entities.back());
				m_systemManager->collisionSystem->AddEntity(m_entities.back()); //TECH RIGHT HERE
				done = true;
			}
			giveUp--;
		}
	}
	holder = (rand() % (chaosFactor / 4)) + 2;
	for (int i = 0; i < holder; i++)
	{
		bool done = false;
		int giveUp = 50;
		while (!done && giveUp > 0)
		{
			int xHolder = rand() % width;
			int yHolder = rand() % height;
			if (mapHolder.at(xHolder).at(yHolder) != "Water" && mapHolder.at(xHolder).at(yHolder) != "DeepWater" && mapHolder.at(xHolder).at(yHolder) != "Town" && mapHolder.at(xHolder).at(yHolder) != "Castle" && mapHolder.at(xHolder).at(yHolder) != "Dungeon" && mapHolder.at(xHolder).at(yHolder) != "DarkCastle")
			{
				mapHolder.at(xHolder).at(yHolder) = "Dungeon";
				m_entities.push_back(factory.Dungeon("WorldTurf", xHolder * (16 * m_systemManager->renderSystem->GetScale()), yHolder * (16 * m_systemManager->renderSystem->GetScale())));
				m_systemManager->renderSystem->AddEntity(m_entities.back());
				m_systemManager->collisionSystem->AddEntity(m_entities.back()); //TECH RIGHT HERE
				done = true;
			}
			giveUp--;
		}
	}

}

void WorldMap::ApplyLake(std::vector<std::vector<std::string>>* map, int x, int y, int radius)
{
	int holderRad = 1;
	bool firstHalf = true;
	while (holderRad != 0)
	{
		if (firstHalf)
		{
			if (holderRad == 0)
			{
				//map->at(x).at(y - radius) = "Water";
			}
			else
			{
				for (int i = -holderRad; i <= holderRad; i++)
				{
					if (i == holderRad && map->at(x + i).at(y - (radius - holderRad)) != "Water" && i == holderRad && map->at(x + i).at(y - (radius - holderRad)) != "DeepWater" || i == -holderRad && map->at(x + i).at(y - (radius - holderRad)) != "Water" && i == -holderRad && map->at(x + i).at(y - (radius - holderRad)) != "DeepWater")
					{
						map->at(x + i).at(y - (radius - holderRad)) = "Desert";
					}
					else if (i < holderRad && i > -holderRad)
					{
						map->at(x + i).at(y - (radius - holderRad)) = "Water";
					}
				}
			}
			holderRad++;
			if (holderRad == radius)
			{
				firstHalf = false;
			}
		}
		else if (!firstHalf)
		{
			if (holderRad == 0)
			{
				//map->at(x).at(y + radius) = "Water";
			}
			else
			{
				for (int i = -holderRad; i <= holderRad; i++)
				{
					if (i == holderRad && map->at(x + i).at(y - (radius - holderRad)) != "Water" && i == holderRad && map->at(x + i).at(y - (radius - holderRad)) != "DeepWater" || i == -holderRad && map->at(x + i).at(y - (radius - holderRad)) != "Water" && i == -holderRad && map->at(x + i).at(y - (radius - holderRad)) != "DeepWater")
					{
						map->at(x + i).at(y + (radius - holderRad)) = "Desert";
					}
					else if (i < holderRad && i > -holderRad)
					{
						map->at(x + i).at(y + (radius - holderRad)) = "Water";
					}
				}
			}
			holderRad--;
		}
		if (map->at(x).at(y - radius) != "Water" && map->at(x).at(y - radius) != "DeepWater")
		{
			map->at(x).at(y - radius) = "Desert";
		}
		if (map->at(x).at(y + radius) != "Water" && map->at(x).at(y - radius) != "DeepWater")
		{
			map->at(x).at(y + radius) = "Desert";
		}
	}
}

void WorldMap::ApplyForest(std::vector<std::vector<std::string>>* map, int x, int y, int radius)
{
	int holderRad = 1;
	bool firstHalf = true;
	while (holderRad != 0)
	{
		if (firstHalf)
		{
			for (int i = -holderRad; i <= holderRad; i++)
			{
				if (map->at(x + i).at(y - (radius - holderRad)) == "Planes")
				{
					map->at(x + i).at(y - (radius - holderRad)) = "Forest";
				}
			}
			holderRad++;
			if (holderRad == radius)
			{
				firstHalf = false;
			}
		}
		else if (!firstHalf)
		{
			for (int i = -holderRad; i <= holderRad; i++)
			{
				if (map->at(x + i).at(y + (radius - holderRad)) == "Planes")
				{
					map->at(x + i).at(y + (radius - holderRad)) = "Forest";
				}
			}
			holderRad--;
		}
	}
}

void WorldMap::ApplyMeadow(std::vector<std::vector<std::string>>* map, int x, int y, int radius)
{
	int holderRad = 1;
	bool firstHalf = true;
	while (holderRad != 0)
	{
		if (firstHalf)
		{
			for (int i = -holderRad; i <= holderRad; i++)
			{
				if (map->at(x + i).at(y - (radius - holderRad)) == "Planes")
				{
					map->at(x + i).at(y - (radius - holderRad)) = "Meadow";
				}
			}
			holderRad++;
			if (holderRad == radius)
			{
				firstHalf = false;
			}
		}
		else if (!firstHalf)
		{
			for (int i = -holderRad; i <= holderRad; i++)
			{
				if (map->at(x + i).at(y + (radius - holderRad)) == "Planes")
				{
					map->at(x + i).at(y + (radius - holderRad)) = "Meadow";
				}
			}
			holderRad--;
		}
	}
}

void WorldMap::ApplyDesert(std::vector<std::vector<std::string>>* map, int x, int y, int radius)
{
	int holderRad = 1;
	bool firstHalf = true;
	while (holderRad != 0)
	{
		if (firstHalf)
		{
			for (int i = -holderRad; i <= holderRad; i++)
			{
				if (map->at(x + i).at(y - (radius - holderRad)) == "Planes")
				{
					map->at(x + i).at(y - (radius - holderRad)) = "Desert";
				}
			}
			holderRad++;
			if (holderRad == radius)
			{
				firstHalf = false;
			}
		}
		else if (!firstHalf)
		{
			for (int i = -holderRad; i <= holderRad; i++)
			{
				if (map->at(x + i).at(y + (radius - holderRad)) == "Planes")
				{
					map->at(x + i).at(y + (radius - holderRad)) = "Desert";
				}
			}
			holderRad--;
		}
	}
}

void WorldMap::ApplySnowField(std::vector<std::vector<std::string>>* map, int x, int y, int radius)
{
	int holderRad = 1;
	bool firstHalf = true;
	while (holderRad != 0)
	{
		if (firstHalf)
		{
			for (int i = -holderRad; i <= holderRad; i++)
			{
				if (map->at(x + i).at(y - (radius - holderRad)) == "Planes")
				{
					map->at(x + i).at(y - (radius - holderRad)) = "SnowField";
				}
			}
			holderRad++;
			if (holderRad == radius)
			{
				firstHalf = false;
			}
		}
		else if (!firstHalf)
		{
			for (int i = -holderRad; i <= holderRad; i++)
			{
				if (map->at(x + i).at(y + (radius - holderRad)) == "Planes")
				{
					map->at(x + i).at(y + (radius - holderRad)) = "SnowField";
				}
			}
			holderRad--;
		}
	}
}

void WorldMap::ApplySnowDune(std::vector<std::vector<std::string>>* map, int x, int y, int radius)
{
	int holderRad = 1;
	bool firstHalf = true;
	while (holderRad != 0)
	{
		if (firstHalf)
		{
			for (int i = -holderRad; i <= holderRad; i++)
			{
				if (map->at(x + i).at(y - (radius - holderRad)) == "SnowField")
				{
					map->at(x + i).at(y - (radius - holderRad)) = "SnowDune";
				}
			}
			holderRad++;
			if (holderRad == radius)
			{
				firstHalf = false;
			}
		}
		else if (!firstHalf)
		{
			for (int i = -holderRad; i <= holderRad; i++)
			{
				if (map->at(x + i).at(y + (radius - holderRad)) == "SnowField")
				{
					map->at(x + i).at(y + (radius - holderRad)) = "SnowDune";
				}
			}
			holderRad--;
		}
	}
}
void WorldMap::ApplyGlacier(std::vector<std::vector<std::string>>* map, int x, int y, int radius)
{
	int holderRad = 1;
	bool firstHalf = true;
	while (holderRad != 0)
	{
		if (firstHalf)
		{
			for (int i = -holderRad; i <= holderRad; i++)
			{
				if (map->at(x + i).at(y - (radius - holderRad)) == "SnowField")
				{
					map->at(x + i).at(y - (radius - holderRad)) = "Glacier";
				}
			}
			holderRad++;
			if (holderRad == radius)
			{
				firstHalf = false;
			}
		}
		else if (!firstHalf)
		{
			for (int i = -holderRad; i <= holderRad; i++)
			{
				if (map->at(x + i).at(y + (radius - holderRad)) == "SnowField")
				{
					map->at(x + i).at(y + (radius - holderRad)) = "Glacier";
				}
			}
			holderRad--;
		}
	}
}

void WorldMap::ApplyDune(std::vector<std::vector<std::string>>* map, int x, int y, int radius)
{
	int holderRad = 1;
	bool firstHalf = true;
	while (holderRad != 0)
	{
		if (firstHalf)
		{
			for (int i = -holderRad; i <= holderRad; i++)
			{
				if (map->at(x + i).at(y - (radius - holderRad)) == "Desert")
				{
					map->at(x + i).at(y - (radius - holderRad)) = "Dune";
				}
			}
			holderRad++;
			if (holderRad == radius)
			{
				firstHalf = false;
			}
		}
		else if (!firstHalf)
		{
			for (int i = -holderRad; i <= holderRad; i++)
			{
				if (map->at(x + i).at(y + (radius - holderRad)) == "Desert")
				{
					map->at(x + i).at(y + (radius - holderRad)) = "Dune";
				}
			}
			holderRad--;
		}
	}
}
void WorldMap::ApplyRock(std::vector<std::vector<std::string>>* map, int x, int y, int radius)
{
	int holderRad = 1;
	bool firstHalf = true;
	while (holderRad != 0)
	{
		if (firstHalf)
		{
			for (int i = -holderRad; i <= holderRad; i++)
			{
				if (map->at(x + i).at(y - (radius - holderRad)) == "Desert")
				{
					map->at(x + i).at(y - (radius - holderRad)) = "Rock";
				}
			}
			holderRad++;
			if (holderRad == radius)
			{
				firstHalf = false;
			}
		}
		else if (!firstHalf)
		{
			for (int i = -holderRad; i <= holderRad; i++)
			{
				if (map->at(x + i).at(y + (radius - holderRad)) == "Desert")
				{
					map->at(x + i).at(y + (radius - holderRad)) = "Rock";
				}
			}
			holderRad--;
		}
	}
}

void WorldMap::Load()
{
	m_active = true;
	m_systemManager->healthSystem->Active(false);

	m_systemManager->controlSystem->SelectiveClear();
	m_systemManager->renderSystem->SelectiveClear();
	m_systemManager->movementSystem->SelectiveClear();
	m_systemManager->collisionSystem->SelectiveClear();
	m_systemManager->attackSystem->SelectiveClear();
	m_systemManager->aiSystem->SelectiveClear();
	m_systemManager->textRenderSystem->SelectiveClear();


	Entity* aplayer = m_systemManager->collisionSystem->FindEntity("Player", 3);

	aplayer->Active(true);

	Entity* aplayer2 = m_systemManager->collisionSystem->FindEntity("Player", 2);

	aplayer2->Active(false);


	Entity* aplayer3 = m_systemManager->collisionSystem->FindEntity("Player", 1);

	aplayer3->Active(false);


	Entity* aplayer4 = m_systemManager->collisionSystem->FindEntity("Player", 0);

	aplayer4->Active(false);

	for (int i = 0; i < m_entities.size(); i++)
	{
		m_systemManager->renderSystem->AddEntity(m_entities.at(i));
		if (m_entities.at(i)->ID() == "Dungeon")
		{
			m_systemManager->collisionSystem->AddEntity(m_entities.at(i));
		}
		else if (m_entities.at(i)->ID() == "Town")
		{
			m_systemManager->collisionSystem->AddEntity(m_entities.at(i));
		}
	}

	// sets player's position to the the previous location on the world map after random encounter
	if (m_listener->EncounterToWorld == true)
	{
		Entity* player = m_systemManager->collisionSystem->FindEntity("Player", 3); //discern between players
		Entity* player2 = m_systemManager->collisionSystem->FindEntity("Player", 2); //discern between players
		Entity* player3 = m_systemManager->collisionSystem->FindEntity("Player", 1); //discern between players
		Entity* player4 = m_systemManager->collisionSystem->FindEntity("Player", 0); //discern between players
		player2->Active(false);
		player3->Active(false);
		player4->Active(false);

		if (player != nullptr)
		{
			CollisionComponent* pos = static_cast<CollisionComponent*>(player->FindComponent("collision"));
		
			if (pos != nullptr)
			{
				pos->setPosition(m_randomEncounterLocation.x, m_randomEncounterLocation.y);
			}
			m_systemManager->healthSystem->HealAllEntities();
		}
		//m_systemManager->healthSystem->DeactivateHearts();
	}

	// sets player's position to the start of the dungeon
	if (m_listener->DungeonToWorld == true)
	{
		Entity* player = m_systemManager->collisionSystem->FindEntity("Player", 3);

		if (player != nullptr)
		{
			CollisionComponent* pos = static_cast<CollisionComponent*>(player->FindComponent("collision"));

			if (pos != nullptr)
			{
				CollisionComponent* dungeonPos = static_cast<CollisionComponent*>(m_systemManager->collisionSystem->getCurrentDungeon()->FindComponent("collision"));

				if (dungeonPos != nullptr)
				{
					pos->setPosition(dungeonPos->getX(), dungeonPos->getY());
				}
			}

			m_systemManager->collisionSystem->getCurrentDungeon()->Active(false);
			m_systemManager->healthSystem->HealAllEntities();
		}
		//m_systemManager->healthSystem->DeactivateHearts();
	}
	if (m_listener->DungeonToWorld == true && m_stateManager->ReturnToWorld == true)
	{
		m_systemManager->collisionSystem->getCurrentDungeon()->Active(true);
		//m_systemManager->healthSystem->DeactivateHearts();
	}

	// sets player's position to the start of the dungeon FGBJFDGFGD
	if (m_listener->TownToWorld == true)
	{
		Entity* player = m_systemManager->collisionSystem->FindEntity("Player", 3);

		player->Active(true);

		Entity* player2 = m_systemManager->collisionSystem->FindEntity("Player", 2);

		player2->Active(false);


		Entity* player3 = m_systemManager->collisionSystem->FindEntity("Player", 1);

		player3->Active(false);


		Entity* player4 = m_systemManager->collisionSystem->FindEntity("Player", 0);

		player4->Active(false);


		if (player != nullptr)
		{
			CollisionComponent* pos = static_cast<CollisionComponent*>(player->FindComponent("collision"));

			if (pos != nullptr)
			{
				CollisionComponent* townPos = static_cast<CollisionComponent*>(m_systemManager->collisionSystem->getCurrentTown()->FindComponent("collision"));

				if (townPos != nullptr)
				{
					pos->setPosition(townPos->getX(), townPos->getY());
				}
			}

			m_systemManager->collisionSystem->getCurrentTown()->Active(false);
		}
	} //SFSFNSDBFJSDBFSDB
	m_listener->ToWorldMap = true;
}

void WorldMap::Update()
{
	// sets player's position to the start of the dungeon
	Entity* player = m_systemManager->movementSystem->FindEntity("Player", 3); //discern between players

	if (player != nullptr)
	{
		MovementComponent* movement = static_cast<MovementComponent*>(player->FindComponent("movement"));

		if (movement != nullptr)
		{
			if (movement->getMoving() == true)
			{
				if ((rand() % 10000) >= 9990)
				{
					if (m_listener->connected == false)
					{
						PositionComponent* pos = static_cast<PositionComponent*>(player->FindComponent("PC"));

						if (pos != nullptr)
						{
							m_randomEncounterLocation = { (int)pos->getX(), (int)pos->getY() };
						}

						m_listener->WorldToEncounter = true;
					}
				}
			}
		}
	}
}