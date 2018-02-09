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
	m_systemManager->AiSystem->SelectiveClear();
	m_systemManager->healthSystem->SelectiveClear();
	m_systemManager->menuSystem->SelectiveClear();
	delete m_factory;

	if (type == "Grassland")
	{
		m_factory = new GrassTileFactory();
	}

	std::vector<Entity*>* projectileEntities = m_systemManager->ProjectileSystem->getEntities();
	
	for (int i = 0; i < 50; i++)
	{
		Entity* projectile = new Entity("Projectile");
		projectile->AddComponent(new SpriteComponent("Arrow", 2, 0, 0, 0, 16, 8, 0));
		projectile->AddComponent(new PositionComponent(SDL_Point{ -5000, -5000 }));
		projectile->AddComponent(new ProjectileComponent(4.9, "Player", 5.0f, 3.0f, 700.0f, false));
		projectile->AddComponent(new MovementComponent());
		projectile->AddComponent(new CollisionComponent());
		projectileEntities->push_back(projectile);
	}
	for (auto i = projectileEntities->begin(), end = projectileEntities->end(); i != end; i++)
	{
		m_systemManager->RenderSystem->AddEntity((*i));
		m_systemManager->MovementSystem->AddEntity((*i));
		m_systemManager->CollisionSystem->AddEntity((*i));
		//m_systemManager->ControlSystem->AddEntity((*i));
	}
	//std::cout << projectileEntities->size() << std::endl;


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

	m_systemManager->AiSystem->Spawn();

	auto aiEntities = m_systemManager->AiSystem->getEntities(); //get and add AI entities to be rendered
	


	for (auto i = aiEntities.begin(), end = aiEntities.end(); i != end; i++)
	{
		m_systemManager->RenderSystem->AddEntity((*i));
		m_systemManager->MovementSystem->AddEntity((*i)); //consider tag discrimination here
	}
	
	Entity * player = new Entity("Player");
	player->AddComponent(new SpriteComponent("Red", 2, 1, 0, 0, 16, 16, 0));
	player->AddComponent(new PositionComponent(SDL_Point{ 100, 300 }));
	player->AddComponent(new AttributesComponent());
	player->AddComponent(new MovementComponent(3));
	player->AddComponent(new CollisionComponent());
	player->AddComponent(new AttributesComponent());

	m_systemManager->ControlSystem->AddEntity(player);
	m_systemManager->MovementSystem->AddEntity(player);
	m_systemManager->RenderSystem->AddEntity(player);
	m_systemManager->ProjectileSystem->AddEntity(player);
	m_systemManager->CollisionSystem->AddEntity(player);
	m_systemManager->healthSystem->AddEntity(player);

	AttributesComponent* ac = new AttributesComponent();
	player->AddComponent(ac);

	HeartManagerComponent* hUI = new HeartManagerComponent(HeartTypes::HEALTH);
	player->AddComponent(hUI);

	HeartManagerComponent* aUI = new HeartManagerComponent(HeartTypes::ARMOUR);
	player->AddComponent(aUI);

	m_systemManager->healthSystem->AddEntity(player);
	m_systemManager->RenderSystem->AddEntity(player);

	m_systemManager->healthSystem->UpdateMaxHeartsUI(player, player);
	m_systemManager->healthSystem->UpdateMaxArmourUI(player, player);

	for (int c = 0; c < hUI->HeartsVector()->size(); c++)
	{
		m_systemManager->RenderSystem->AddEntity(hUI->HeartsVector()->at(c));
	}
	for (int i = 0; i < aUI->HeartsVector()->size(); i++)
	{
		m_systemManager->RenderSystem->AddEntity(aUI->HeartsVector()->at(i));
	}
}
void BattleMap::Update()
{

}
void BattleMap::Render()
{

}