#include "InstanceManager.h"

InstanceManager::InstanceManager(StateManager * stateManager, ResourceManager * resourceManager, InputHandler * input, EventListener * eventListener, SDL_Renderer * sdlr)
{
	m_stateManager = stateManager;
	m_resourceManager = resourceManager;
	m_input = input;
	m_eventListener = eventListener;
	m_sdlr = sdlr;
	m_instances.push_back(new StartInstance(m_systemManager, m_sdlr, m_stateManager));
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
}