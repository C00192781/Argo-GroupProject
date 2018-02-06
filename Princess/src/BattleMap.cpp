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
	delete m_factory;

	if (type == "Grassland")
	{
		m_factory = new GrassTileFactory();
	}

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

	//for (int c = 0; c < hUI->HeartsVector()->size(); c++)
	//{
	//	m_systemManager->RenderSystem->AddEntity(hUI->HeartsVector()->at(c));
	//}
	//for (int i = 0; i < aUI->HeartsVector()->size(); i++)
	//{
	//	m_systemManager->RenderSystem->AddEntity(aUI->HeartsVector()->at(i));
	//}
}
void BattleMap::Update()
{

}
void BattleMap::Render()
{

}