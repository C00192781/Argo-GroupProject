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
	m_systemManager->ControlSystem->SelectiveClear();
	m_systemManager->RenderSystem->SelectiveClear();
	m_systemManager->MovementSystem->SelectiveClear();

	TileFactory * factory;

	if (type == "Grassland")
	{
		factory = new GrassTileFactory();
	}
	else
	{
		factory = new GrassTileFactory();
	}

	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			int rando = rand() % 100;
			if (rando <= 80)
			{
				m_entities.push_back(factory->GroundA("Turf", i * (16 * m_systemManager->RenderSystem->GetScale()), j * (16 * m_systemManager->RenderSystem->GetScale())));
			}
			else if (rando <= 90)
			{
				m_entities.push_back(factory->GroundB("Turf", i * (16 * m_systemManager->RenderSystem->GetScale()), j * (16 * m_systemManager->RenderSystem->GetScale())));
			}																		
			else if (rando <= 95)													
			{																		
				m_entities.push_back(factory->GroundC("Turf", i * (16 * m_systemManager->RenderSystem->GetScale()), j * (16 * m_systemManager->RenderSystem->GetScale())));
			}																		
			else																	
			{																		
				m_entities.push_back(factory->GroundD("Turf", i * (16 * m_systemManager->RenderSystem->GetScale()), j * (16 * m_systemManager->RenderSystem->GetScale())));
			}
			m_systemManager->RenderSystem->AddEntity(m_entities.back());
		}
	}

	delete factory;
}
void BattleMap::Update()
{

}
void BattleMap::Render()
{

}