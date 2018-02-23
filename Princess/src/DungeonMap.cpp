#include "DungeonMap.h"

DungeonMap::DungeonMap(SystemManager * sm, StateManager * s, ResourceManager * rm, EventListener *listener, AStar *aStar)
{
	m_systemManager = sm;
	m_stateManager = s;
	m_resourceManager = rm;
	m_listener = listener;
	m_aStar = aStar;

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
	m_timeRemaining = 5;
	m_active = true;
	for (int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities.at(i);
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		delete m_enemies.at(i);
	}
	m_entities.clear();
	m_enemies.clear();
	m_pickups.clear();
	m_pickups.shrink_to_fit();
	m_entities.shrink_to_fit();
	m_enemies.shrink_to_fit();
	m_systemManager->controlSystem->SelectiveClear();
	m_systemManager->renderSystem->SelectiveClear();
	m_systemManager->movementSystem->SelectiveClear();
	m_systemManager->collisionSystem->SelectiveClear();
	m_systemManager->aiSystem->SelectiveClear();
	m_systemManager->healthSystem->SelectiveClear();

	m_systemManager->healthSystem->Active(true);

	int randomMapNumber = rand() % 5;
	std::string mapName;

	if (randomMapNumber == 0)
	{
		mapName = "DungeonMap1";
		m_listener->ToDungeon1 = true;
		m_aStar->setCurrentDungeon(1);
	}
	else if (randomMapNumber == 1)
	{
		mapName = "DungeonMap2";
		m_listener->ToDungeon2 = true;
		m_aStar->setCurrentDungeon(2);
	}
	else if (randomMapNumber == 2)
	{
		mapName = "DungeonMap3";
		m_listener->ToDungeon3 = true;
		m_aStar->setCurrentDungeon(3);
	}
	else if (randomMapNumber == 3)
	{
		mapName = "DungeonMap4";
		m_listener->ToDungeon4 = true;
		m_aStar->setCurrentDungeon(4);
	}
	else
	{
		mapName = "DungeonMap5";
		m_listener->ToDungeon5 = true;
		m_aStar->setCurrentDungeon(5);
	}

	DungeonTileFactory factory;
	BasicEnemy enemyFactory;
	Pickup pickupFactory;

	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			if (m_resourceManager->GetMapElement(mapName, i, j) == "W")
			{
				m_entities.push_back(factory.Wall("DungeonTiles", j, i, m_systemManager->renderSystem->GetScale()));
				m_systemManager->renderSystem->AddEntity(m_entities.back());
				m_systemManager->collisionSystem->AddEntity(m_entities.back());
			}
			else if (m_resourceManager->GetMapElement(mapName, i, j) == "F")
			{
				m_entities.push_back(factory.Floor("DungeonTiles", j, i, m_systemManager->renderSystem->GetScale()));
				m_systemManager->renderSystem->AddEntity(m_entities.back());
			}
			else if (m_resourceManager->GetMapElement(mapName, i, j) == "P")
			{
				m_entities.push_back(factory.Floor("DungeonTiles", j, i, m_systemManager->renderSystem->GetScale()));
				m_systemManager->renderSystem->AddEntity(m_entities.back());
				m_startPoint = { j * (int)m_systemManager->renderSystem->GetScale() * 16, i * (int)m_systemManager->renderSystem->GetScale() * 16 };

				// sets player's position to the start of the dungeon

			//	Entity* player = m_systemManager->collisionSystem->FindEntity("Player");

				Entity* player = m_systemManager->collisionSystem->FindEntity("Player", 3); //discern between players
				Entity* player2 = m_systemManager->collisionSystem->FindEntity("Player", 2); //discern between players
				Entity* player3 = m_systemManager->collisionSystem->FindEntity("Player", 1); //discern between players
				Entity* player4 = m_systemManager->collisionSystem->FindEntity("Player", 0); //discern between players
				player2->Active(true);
				player3->Active(true);
				player4->Active(true);
				
				if (player != nullptr)
				{
					CollisionComponent* pos = static_cast<CollisionComponent*>(player->FindComponent("collision"));

					if (pos != nullptr)
					{
						pos->setPosition(m_startPoint.x, m_startPoint.y);
					}
				}



				if (player2 != nullptr)
				{
					CollisionComponent* pos = static_cast<CollisionComponent*>(player2->FindComponent("collision"));

					if (pos != nullptr)
					{
						pos->setPosition(m_startPoint.x + 50, m_startPoint.y);
					}
				}

				if (player3 != nullptr)
				{
					CollisionComponent* pos = static_cast<CollisionComponent*>(player3->FindComponent("collision"));

					if (pos != nullptr)
					{
						pos->setPosition(m_startPoint.x, m_startPoint.y +50);
					}
				}


				if (player4 != nullptr)
				{
					CollisionComponent* pos = static_cast<CollisionComponent*>(player3->FindComponent("collision"));

					if (pos != nullptr)
					{
						pos->setPosition(m_startPoint.x + 50, m_startPoint.y + 50);
					}
				}

				//more player pos here 
			}
			else if (m_resourceManager->GetMapElement(mapName, i, j) == "E") //make a == "X" for pickups or w/e
			{
			
				if (m_enemies.size() < 10)
				{
					m_entities.push_back(factory.Floor("DungeonTiles", j, i, m_systemManager->renderSystem->GetScale()));
					m_systemManager->renderSystem->AddEntity(m_entities.back());

					int randNum = rand() % 5;

					Entity* enemy = nullptr;
					Entity* pickup = nullptr;
					//ADD SOME ITEM SPAWNS AROUND HERE
					if (randNum == 0) {
						enemy = enemyFactory.CharA("Blue", SDL_Point{ j * (int)m_systemManager->renderSystem->GetScale() * 16, i * (int)m_systemManager->renderSystem->GetScale() * 16 }, 0);
						pickup = pickupFactory.PickupA("Pickup", SDL_Point{ j * (int)m_systemManager->renderSystem->GetScale() * 16, i * (int)m_systemManager->renderSystem->GetScale() * 16 }, 50);
					}
					else if (randNum == 1)
					{
						enemy = enemyFactory.CharB("Blue", SDL_Point{ j * (int)m_systemManager->renderSystem->GetScale() * 16, i * (int)m_systemManager->renderSystem->GetScale() * 16 }, 0);
						pickup = pickupFactory.PickupB("Pickup", SDL_Point{ j * (int)m_systemManager->renderSystem->GetScale() * 16, i * (int)m_systemManager->renderSystem->GetScale() * 16 }, 100);
					}
					else if (randNum == 2)
					{
						enemy = enemyFactory.CharC("Blue", SDL_Point{ j * (int)m_systemManager->renderSystem->GetScale() * 16, i * (int)m_systemManager->renderSystem->GetScale() * 16 }, 0);
						pickup = pickupFactory.PickupC("Pickup", SDL_Point{ j * (int)m_systemManager->renderSystem->GetScale() * 16, i * (int)m_systemManager->renderSystem->GetScale() * 16 }, 150);
					}
					else if (randNum == 3)
					{
						enemy = enemyFactory.CharD("Blue", SDL_Point{ j * (int)m_systemManager->renderSystem->GetScale() * 16, i * (int)m_systemManager->renderSystem->GetScale() * 16 }, 0);

						pickup = pickupFactory.PickupD("Pickup", SDL_Point{ j * (int)m_systemManager->renderSystem->GetScale() * 16, i * (int)m_systemManager->renderSystem->GetScale() * 16 }, 200);
					}

					// chance for spawner to not spawn anything
					if (enemy != nullptr)
					{
						enemy->Active(true);


						m_enemies.push_back(enemy);
						m_systemManager->renderSystem->AddEntity(enemy);
						m_systemManager->movementSystem->AddEntity(enemy);
						m_systemManager->collisionSystem->AddEntity(enemy);
						m_systemManager->aiSystem->AddEntity(enemy);

						m_systemManager->attackSystem->AddEntity(enemy);
					}
					if (pickup != nullptr)
					{
						pickup->Active(true);

						m_pickups.push_back(pickup);
						m_systemManager->renderSystem->AddEntity(pickup);
						m_systemManager->collisionSystem->AddEntity(pickup);
					}
				}
			}
		}
	}

	std::vector<Entity*>* projectileEntities = m_systemManager->attackSystem->getProjectiles();

	for (int i = 0; i < 100; i++)
	{
		Entity* projectile = new Entity("Projectile");
		projectile->AddComponent(new SpriteComponent("Arrow", 2, 0, 0, 0, 4, 4, 0));
		projectile->AddComponent(new PositionComponent(SDL_Point{ -5000, -5000 }));
		projectile->AddComponent(new ProjectileComponent(400));
		projectile->AddComponent(new MovementComponent());
		projectile->AddComponent(new CollisionComponent(-5000, -5000, 10, 10, 2));
		projectile->Active(false);
		projectileEntities->push_back(projectile);
	}
	for (auto i = projectileEntities->begin(), end = projectileEntities->end(); i != end; i++)
	{
		m_systemManager->renderSystem->AddEntity((*i));
		m_systemManager->movementSystem->AddEntity((*i));
		m_systemManager->collisionSystem->AddEntity((*i));
		m_systemManager->attackSystem->AddEntity((*i));
	}

	std::cout << projectileEntities->size() << std::endl;

	//m_systemManager->healthSystem->ActivateHearts();

	m_systemManager->collisionSystem->updateBounds(SDL_Rect{0, 0, 16 * 24 * (int)m_systemManager->renderSystem->GetScale(), 16 * 24 * (int)m_systemManager->renderSystem->GetScale() });
}

void DungeonMap::Generate(std::string mapName)
{
	m_timeRemaining = 5;
	m_active = true;

	for (int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities.at(i);
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		delete m_enemies.at(i);
	}
	m_entities.clear();
	m_enemies.clear();
	m_pickups.clear();
	m_pickups.shrink_to_fit();
	m_entities.shrink_to_fit();
	m_enemies.shrink_to_fit();
	m_systemManager->controlSystem->SelectiveClear();
	m_systemManager->renderSystem->SelectiveClear();
	m_systemManager->movementSystem->SelectiveClear();
	m_systemManager->collisionSystem->SelectiveClear();
	m_systemManager->aiSystem->SelectiveClear();

	DungeonTileFactory factory;
	BasicEnemy enemyFactory;
	Pickup pickupFactory;

	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			if (m_resourceManager->GetMapElement(mapName, i, j) == "W")
			{
				m_entities.push_back(factory.Wall("DungeonTiles", j, i, m_systemManager->renderSystem->GetScale()));
				m_systemManager->renderSystem->AddEntity(m_entities.back());
				m_systemManager->collisionSystem->AddEntity(m_entities.back());
			}
			else if (m_resourceManager->GetMapElement(mapName, i, j) == "F")
			{
				m_entities.push_back(factory.Floor("DungeonTiles", j, i, m_systemManager->renderSystem->GetScale()));
				m_systemManager->renderSystem->AddEntity(m_entities.back());
			}
			else if (m_resourceManager->GetMapElement(mapName, i, j) == "P")
			{
				m_entities.push_back(factory.Floor("DungeonTiles", j, i, m_systemManager->renderSystem->GetScale()));
				m_systemManager->renderSystem->AddEntity(m_entities.back());
				m_startPoint = { j * (int)m_systemManager->renderSystem->GetScale() * 16, i * (int)m_systemManager->renderSystem->GetScale() * 16 };

				Entity* player = m_systemManager->collisionSystem->FindEntity("Player", 3); //discern between players
				Entity* player2 = m_systemManager->collisionSystem->FindEntity("Player", 2); //discern between players
				Entity* player3 = m_systemManager->collisionSystem->FindEntity("Player", 1); //discern between players
				Entity* player4 = m_systemManager->collisionSystem->FindEntity("Player", 0); //discern between players
				player2->Active(true);
				player3->Active(true);
				player4->Active(true);

				if (player != nullptr)
				{
					CollisionComponent* pos = static_cast<CollisionComponent*>(player->FindComponent("collision"));

					if (pos != nullptr)
					{
						pos->setPosition(m_startPoint.x, m_startPoint.y);
					}
				}


				if (player2 != nullptr)
				{
					CollisionComponent* pos = static_cast<CollisionComponent*>(player2->FindComponent("collision"));

					if (pos != nullptr)
					{
						pos->setPosition(m_startPoint.x + 50, m_startPoint.y);
					}
				}

				if (player3 != nullptr)
				{
					CollisionComponent* pos = static_cast<CollisionComponent*>(player3->FindComponent("collision"));

					if (pos != nullptr)
					{
						pos->setPosition(m_startPoint.x, m_startPoint.y + 50);
					}
				}


				if (player4 != nullptr)
				{
					CollisionComponent* pos = static_cast<CollisionComponent*>(player3->FindComponent("collision"));

					if (pos != nullptr)
					{
						pos->setPosition(m_startPoint.x + 50, m_startPoint.y + 50);
					}
				}
			}
			else if (m_resourceManager->GetMapElement(mapName, i, j) == "E") //make a == "X" for pickups or w/e
			{
				if (m_enemies.size() < 2)
				{
					m_entities.push_back(factory.Floor("DungeonTiles", j, i, m_systemManager->renderSystem->GetScale()));
					m_systemManager->renderSystem->AddEntity(m_entities.back());

					int randNum = rand() % 5;

					Entity* enemy = nullptr;
					Entity* pickup = nullptr;
					//ADD SOME ITEM SPAWNS AROUND HERE
					if (randNum == 0) {
						enemy = enemyFactory.CharA("Demon", SDL_Point{ j * (int)m_systemManager->renderSystem->GetScale() * 16, i * (int)m_systemManager->renderSystem->GetScale() * 16 }, 0);
					}
					else if (randNum == 1)
					{
						enemy = enemyFactory.CharB("Demon", SDL_Point{ j * (int)m_systemManager->renderSystem->GetScale() * 16, i * (int)m_systemManager->renderSystem->GetScale() * 16 }, 0);
					}
					else if (randNum == 2)
					{
						enemy = enemyFactory.CharC("Demon", SDL_Point{ j * (int)m_systemManager->renderSystem->GetScale() * 16, i * (int)m_systemManager->renderSystem->GetScale() * 16 }, 0);
					}
					else if (randNum == 3)
					{
						enemy = enemyFactory.CharD("Demon", SDL_Point{ j * (int)m_systemManager->renderSystem->GetScale() * 16, i * (int)m_systemManager->renderSystem->GetScale() * 16 }, 0);

						pickup = pickupFactory.PickupA("Red", SDL_Point{ j * (int)m_systemManager->renderSystem->GetScale() * 16, i * (int)m_systemManager->renderSystem->GetScale() * 16 }, 5);
					}

					// chance for spawner to not spawn anything
					if (enemy != nullptr)
					{
						enemy->Active(true);


						m_enemies.push_back(enemy);
						m_systemManager->renderSystem->AddEntity(enemy);
						m_systemManager->movementSystem->AddEntity(enemy);
						m_systemManager->collisionSystem->AddEntity(enemy);
						m_systemManager->aiSystem->AddEntity(enemy);

						m_systemManager->attackSystem->AddEntity(enemy);
					}
					if (pickup != nullptr)
					{
						pickup->Active(true);

						m_pickups.push_back(pickup);
						m_systemManager->renderSystem->AddEntity(pickup);
						m_systemManager->collisionSystem->AddEntity(pickup);
					}
				}
			}
		}
	}

	std::vector<Entity*>* projectileEntities = m_systemManager->attackSystem->getProjectiles();

	for (int i = 0; i < 100; i++)
	{
		Entity* projectile = new Entity("Projectile");
		projectile->AddComponent(new SpriteComponent("Arrow", 2, 0, 0, 0, 16, 8, 0));
		projectile->AddComponent(new PositionComponent(SDL_Point{ -5000, -5000 }));
		projectile->AddComponent(new ProjectileComponent(400));
		projectile->AddComponent(new MovementComponent());
		projectile->AddComponent(new CollisionComponent(-5000, -5000, 10, 10, 2));
		projectile->Active(false);
		projectileEntities->push_back(projectile);
	}
	for (auto i = projectileEntities->begin(), end = projectileEntities->end(); i != end; i++)
	{
		m_systemManager->renderSystem->AddEntity((*i));
		m_systemManager->movementSystem->AddEntity((*i));
		m_systemManager->collisionSystem->AddEntity((*i));
		m_systemManager->attackSystem->AddEntity((*i));
	}

	std::cout << projectileEntities->size() << std::endl;

	m_systemManager->collisionSystem->updateBounds(SDL_Rect{ 0, 0, 16 * 24 * (int)m_systemManager->renderSystem->GetScale(), 16 * 24 * (int)m_systemManager->renderSystem->GetScale() });
}

void DungeonMap::Update(float deltaTime)
{
	for (int i = 0; i < m_enemies.size();)
	{
		if (m_enemies.at(i)->Active() == false)
		{
			m_enemies.erase(m_enemies.begin() + i);
		}
		else
		{
			i++;
		}
	}

	for (int i = 0; i < m_pickups.size();)
	{
		if (m_pickups.at(i)->Active() == false)
		{
			m_pickups.erase(m_pickups.begin() + i);
		}
		else
		{
			i++;
		}
	}

	if (m_enemies.empty())
	{
		m_timeRemaining -= deltaTime;

		if (m_timeRemaining <= 0)
		{
			m_systemManager->healthSystem->Active(false);
			m_listener->DungeonToWorld = true;
		}
	}

	
}