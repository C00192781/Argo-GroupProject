#include "BattleMap.h"



BattleMap::BattleMap(SystemManager * sm, SDL_Renderer * sdlr, StateManager * s)
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
	m_systemManager->ControlSystem->SelectiveClear();
	m_systemManager->RenderSystem->SelectiveClear();
	m_systemManager->MovementSystem->SelectiveClear();

	delete m_factory;

	if (type == "Grassland")
	{
		m_factory = new GrassTileFactory();
	}

	std::vector<Entity*>* projectileEntities = m_systemManager->ProjectileSystem->getEntities();

	for (int i = 0; i < 50; i++)
	{
		Entity* projectile = new Entity("Projectile");
		projectile->AddComponent(new SpriteComponent("Red", 2, 1, 0, 0, 16, 16, 0));
		projectile->AddComponent(new PositionComponent(SDL_Point{ i + 600, i + 300 }));
		projectile->AddComponent(new ProjectileComponent(4.9, "Enemy", 5.0f, 3.0f, 10.0f));
		projectile->AddComponent(new MovementComponent());
		projectile->AddComponent(new CollisionComponent());
		projectileEntities->push_back(projectile);
	}
	for (auto i = projectileEntities->begin(), end = projectileEntities->end(); i != end; i++)
	{
		m_systemManager->RenderSystem->AddEntity((*i));
		m_systemManager->MovementSystem->AddEntity((*i));
		m_systemManager->CollisionSystem->AddEntity((*i));
	}
	std::cout << projectileEntities->size() << std::endl;





	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			int rando = rand() % 100;
			if (rando <= 80)
			{
				m_entities.push_back(m_factory->GroundA("Turf", i * (16 * m_systemManager->RenderSystem->GetScale()), j * (16 * m_systemManager->RenderSystem->GetScale())));
			}
			else if (rando <= 90)
			{
				m_entities.push_back(m_factory->GroundB("Turf", i * (16 * m_systemManager->RenderSystem->GetScale()), j * (16 * m_systemManager->RenderSystem->GetScale())));
			}																			
			else if (rando <= 95)														
			{																			
				m_entities.push_back(m_factory->GroundC("Turf", i * (16 * m_systemManager->RenderSystem->GetScale()), j * (16 * m_systemManager->RenderSystem->GetScale())));
			}																			
			else																		
			{																			
				m_entities.push_back(m_factory->GroundD("Turf", i * (16 * m_systemManager->RenderSystem->GetScale()), j * (16 * m_systemManager->RenderSystem->GetScale())));
			}
			m_systemManager->RenderSystem->AddEntity(m_entities.back());
		}
	}

	
}
void BattleMap::Update()
{

}
void BattleMap::Render()
{

}