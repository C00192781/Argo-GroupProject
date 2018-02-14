#include "BattleMap.h"



BattleMap::BattleMap(SystemManager * sm, StateManager * s)
{
	m_systemManager = sm;
	m_stateManager = s;
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
	m_entities.clear();
	m_entities.shrink_to_fit();
	m_systemManager->controlSystem->SelectiveClear();
	m_systemManager->renderSystem->SelectiveClear();
	m_systemManager->movementSystem->SelectiveClear();

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
	
	for (int i = 0; i < 100; i++)
	{
		Entity* projectile = new Entity("Projectile");
		projectile->AddComponent(new SpriteComponent("Arrow", 2, 0, 0, 0, 16, 8, 0));
		projectile->AddComponent(new PositionComponent(SDL_Point{ -5000, -5000 }));
		projectile->AddComponent(new ProjectileComponent(10));
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

	m_systemManager->aiSystem->Spawn();

	auto aiEntities = m_systemManager->aiSystem->getEntities(); //get and add AI entities to be rendered

	for (auto i = aiEntities.begin(), end = aiEntities.end(); i != end; i++)
	{
		m_systemManager->renderSystem->AddEntity((*i));
		m_systemManager->movementSystem->AddEntity((*i)); //consider tag discrimination here
		m_systemManager->collisionSystem->AddEntity((*i));
	}

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

	delete factory;
}
void BattleMap::Update()
{

}
void BattleMap::Render()
{

}