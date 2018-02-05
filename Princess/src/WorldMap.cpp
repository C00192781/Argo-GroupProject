#include "WorldMap.h"

WorldMap::WorldMap(SystemManager * sm, StateManager * s)
{
	m_systemManager = sm;
	m_stateManager = s;
}

WorldMap::~WorldMap()
{
}

void WorldMap::Generate(int width, int height, int chaosFactor)
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

	WorldTileFactory factory;

	std::vector<std::vector<std::string>> mapHolder;

	for (int i = 0; i < width + 12; i++)
	{
		std::vector<std::string> holder;
		for (int j = 0; j < height + 12; j++)
		{
			holder.push_back("Water");
		}
		mapHolder.push_back(holder);
	}


	for (int i = 0; i < width + 12; i++)
	{
		for (int j = 0; j < height + 12; j++)
		{
			if (i > 5 && i < width + 6 && j > 5 && j < height + 6)
			{
				if (i == 6 || i == width + 5 || j == 6 || j == height + 5)
				{
					int rando = rand() % 100;
					if (rando >= 10)
					{
						mapHolder.at(i).at(j) = "Desert";
					}
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

	for (int i = 0; i < width + 12; i++)
	{
		for (int j = 0; j < height + 12; j++)
		{
			if (mapHolder.at(i).at(j) == "Water")
			{
				m_entities.push_back(factory.Water("WorldTurf", i * (16 * m_systemManager->RenderSystem->GetScale()), j * (16 * m_systemManager->RenderSystem->GetScale())));
			}
			else if (mapHolder.at(i).at(j) == "Desert")
			{
				m_entities.push_back(factory.Desert("WorldTurf", i * (16 * m_systemManager->RenderSystem->GetScale()), j * (16 * m_systemManager->RenderSystem->GetScale())));
			}
			else if (mapHolder.at(i).at(j) == "Planes")
			{
				m_entities.push_back(factory.Planes("WorldTurf", i * (16 * m_systemManager->RenderSystem->GetScale()), j * (16 * m_systemManager->RenderSystem->GetScale())));
			}
			m_systemManager->RenderSystem->AddEntity(m_entities.back());
		}
	}
}

void WorldMap::Load()
{

}

void WorldMap::Update()
{

}

void WorldMap::Render()
{

}