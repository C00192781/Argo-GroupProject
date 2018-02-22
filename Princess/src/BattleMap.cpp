#include "BattleMap.h"



BattleMap::BattleMap(SystemManager * sm, StateManager * s, EventListener* listener)
{
	m_systemManager = sm;
	m_stateManager = s;
	m_listener = listener;
	m_timeRemaining = 2;
}

BattleMap::~BattleMap()
{
}

void BattleMap::Generate(std::string type)
{
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
	m_entities.shrink_to_fit();
	m_enemies.shrink_to_fit();
	m_systemManager->controlSystem->SelectiveClear();
	m_systemManager->renderSystem->SelectiveClear();
	m_systemManager->movementSystem->SelectiveClear();
	m_systemManager->collisionSystem->SelectiveClear();
	m_systemManager->aiSystem->SelectiveClear();

	TileFactory * factory;

	if (type == "Grassland")
	{
		factory = new GrassTileFactory();
	}
	else
	{
		factory = new GrassTileFactory();
	}
	std::vector<Entity*>* projectileEntities = m_systemManager->attackSystem->getProjectiles();
	projectileEntities->clear();

	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			int rando = rand() % 100;
			if (rando <= 80)
			{
				m_entities.push_back(factory->GroundA("Turf", i * (16 * m_systemManager->renderSystem->GetScale()), j * (16 * m_systemManager->renderSystem->GetScale())));
			}
			else if (rando <= 90)
			{
				m_entities.push_back(factory->GroundB("Turf", i * (16 * m_systemManager->renderSystem->GetScale()), j * (16 * m_systemManager->renderSystem->GetScale())));
			}
			else if (rando <= 95)
			{
				m_entities.push_back(factory->GroundC("Turf", i * (16 * m_systemManager->renderSystem->GetScale()), j * (16 * m_systemManager->renderSystem->GetScale())));
			}
			else
			{
				m_entities.push_back(factory->GroundD("Turf", i * (16 * m_systemManager->renderSystem->GetScale()), j * (16 * m_systemManager->renderSystem->GetScale())));
			}
			m_systemManager->renderSystem->AddEntity(m_entities.back());
		}
	}

	int numOfEnemies = 5;//(rand() % 10) + 5;

	BasicEnemy enemyFactory;

	for (int i = 0; i < numOfEnemies; i++)
	{
		int randNum = rand() % 5;

		Entity* enemy = nullptr;

		if (randNum == 0) {
			enemy = enemyFactory.CharA("Demon", SDL_Point{ rand() % 816, rand() % 624 }, 0);
		}
		else if (randNum == 1)
		{
			enemy = enemyFactory.CharB("Demon", SDL_Point{ rand() % 816, rand() % 624 }, 0);
		}
		else if (randNum == 2)
		{
			enemy = enemyFactory.CharC("Demon", SDL_Point{ rand() % 816, rand() % 624 }, 0);
		}
		else if (randNum == 3)
		{
			enemy = enemyFactory.CharD("Demon", SDL_Point{ rand() % 816, rand() % 624 }, 0);
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
	}
	
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


	// sets player's position to the start of the dungeon
	Entity* player = m_systemManager->collisionSystem->FindEntity("Player");


	if (player != nullptr)
	{
		CollisionComponent* pos = static_cast<CollisionComponent*>(player->FindComponent("collision"));

		if (pos != nullptr)
		{
			pos->setPosition(274, 208);
		}
	}

	m_timeRemaining = 2;
	m_active = true;

	delete factory;
}
void BattleMap::Update(float deltaTime)
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

	if (m_enemies.empty())
	{
		m_timeRemaining -= deltaTime;

		if (m_timeRemaining <= 0)
		{
			m_listener->EncounterToWorld = true;
		}
	}
}
void BattleMap::Render()
{

}

// *** this was at the bottom of generate ***
//HeartManagerComponent* hUI = new HeartManagerComponent(HeartTypes::HEALTH);
//player->AddComponent(hUI);
//
//HeartManagerComponent* aUI = new HeartManagerComponent(HeartTypes::ARMOUR);
//player->AddComponent(aUI);

//m_systemManager->healthSystem->AddEntity(player);
//
//m_systemManager->healthSystem->UpdateMaxHeartsUI(player, player);
//m_systemManager->healthSystem->UpdateMaxArmourUI(player, player);

//for (int c = 0; c < hUI->HeartsVector()->size(); c++)
//{
//	m_systemManager->renderSystem->AddEntity(hUI->HeartsVector()->at(c));
//}
//for (int i = 0; i < aUI->HeartsVector()->size(); i++)
//{
//	m_systemManager->renderSystem->AddEntity(aUI->HeartsVector()->at(i));
//}