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
	m_systemManager->AiSystems->SelectiveClear();
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

	m_systemManager->AiSystems->Spawn();

	auto aiEntities = m_systemManager->AiSystems->getEntities(); //get and add AI entities to be rendered
	


	for (auto i = aiEntities.begin(), end = aiEntities.end(); i != end; i++)
	{
		m_systemManager->RenderSystem->AddEntity((*i));
		m_systemManager->MovementSystem->AddEntity((*i)); //consider tag discrimination here
		m_systemManager->CollisionSystem->AddEntity((*i));
	}

}
void BattleMap::Update()
{

}
void BattleMap::Render()
{

}