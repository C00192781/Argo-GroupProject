#include "BattleMap.h"



BattleMap::BattleMap(ResourceManager * r, SDL_Renderer * sdlr, EventListener * e, StateManager * s, int scale)
{
	m_renderSystem = new RenderSystem(r, sdlr);
	m_controlSystem = new ControlSystem(e);
	m_movementSystem = new MovementSystem();
	m_renderSystem->SetScale(scale);
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
	m_renderSystem->ClearEntities();
	m_controlSystem->ClearEntities();
	m_movementSystem->ClearEntities();

	delete m_factory;

	if (type == "Grassland")
	{
		m_factory = new GrassTileFactory();
	}

	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			int rando = rand() % 15;
			if (rando <= 6)
			{
				m_entities.push_back(m_factory->GroundA("Turf", i * (16 * m_renderSystem->GetScale()), j * (16 * m_renderSystem->GetScale())));
			}
			else if (rando <= 9)
			{
				m_entities.push_back(m_factory->GroundB("Turf", i * (16 * m_renderSystem->GetScale()), j * (16 * m_renderSystem->GetScale())));
			}																			
			else if (rando <= 13)														
			{																			
				m_entities.push_back(m_factory->GroundC("Turf", i * (16 * m_renderSystem->GetScale()), j * (16 * m_renderSystem->GetScale())));
			}																			
			else																		
			{																			
				m_entities.push_back(m_factory->GroundD("Turf", i * (16 * m_renderSystem->GetScale()), j * (16 * m_renderSystem->GetScale())));
			}
			m_renderSystem->AddEntity(m_entities.back());
		}
	}

}
void BattleMap::Update()
{
	m_controlSystem->Update();
}
void BattleMap::Render()
{
	m_renderSystem->Update();
}