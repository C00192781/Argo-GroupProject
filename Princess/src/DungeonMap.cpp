#include "DungeonMap.h"

DungeonMap::DungeonMap(SystemManager * sm, StateManager * s, ResourceManager * rm)
{
	m_systemManager = sm;
	m_stateManager = s;
	m_resourceManager = rm;

	m_resourceManager->AddMap("DungeonMap1", "DungeonMap1.json");
}

void DungeonMap::generate()
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

	//if (m_resourceManager->GetMapElement("DungeonMap1", 0, 0) == "T")
	//{
	//	//std::cout << "AY LMAO" << std::endl;
	//}
	//else if (m_resourceManager)
}