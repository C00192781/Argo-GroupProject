#include "InstanceManager.h"

InstanceManager::InstanceManager(StateManager * stateManager, ResourceManager * resourceManager, InputHandler * input, EventListener * eventListener, SDL_Renderer * sdlr, SystemManager * systemManager)
{
	m_stateManager = stateManager;
	m_resourceManager = resourceManager;
	m_input = input;
	m_eventListener = eventListener;
	m_sdlr = sdlr;
	m_systemManager = systemManager;
	m_instances.push_back(new StartInstance(m_systemManager, m_sdlr, m_stateManager));
	static_cast<StartInstance*>(m_instances.at(m_instances.size() - 1))->Begin();
	m_systemManager->renderSystem->Camera(false);
}

InstanceManager::~InstanceManager()
{

}

void InstanceManager::Update()
{
	for (int i = 0; i < m_instances.size(); i++)
	{
		m_instances.at(i)->Update();
	}
	if (m_stateManager->StartGame)
	{
		if (m_instances.at(0)->ID() == "StartInstance")
		{
			static_cast<StartInstance*>(m_instances.at(m_instances.size() - 1))->~StartInstance();
			m_instances.erase(m_instances.begin());
		}
		m_systemManager->renderSystem->Camera(true);
		m_instances.push_back(new BattleMap(m_systemManager, m_stateManager));
		static_cast<BattleMap*>(m_instances.at(m_instances.size() - 1))->Generate("Grassland");
		m_stateManager->StartGame = false;
	}
}