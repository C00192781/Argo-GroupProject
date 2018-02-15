#include "StartInstance.h"

StartInstance::StartInstance(SystemManager * sm, SDL_Renderer * sdlr, StateManager * s)
{
	m_id = "StartInstance";
	m_systemManager = sm;
	m_stateManager = s;

}

StartInstance::~StartInstance()
{
	m_systemManager->menuSystem->RemoveMenu("MainMenu");
	m_systemManager->menuSystem->RemoveMenu("OptionsMenu");
}

void StartInstance::Begin()
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

	m_systemManager->menuSystem->SetUpOptionsMenu();
	m_systemManager->menuSystem->SetUpMainMenu();
	m_systemManager->menuSystem->ChangeMenu("MainMenu");
	for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->size(); i++)
	{
		m_systemManager->renderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i));
	}
}

void StartInstance::Update()
{
	if (m_stateManager->Options)
	{
		for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->size(); i++)
		{
			m_systemManager->renderSystem->RemoveEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->ID());
		}
		m_systemManager->menuSystem->ChangeMenu("OptionsMenu");
		for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->size(); i++)
		{
			m_systemManager->renderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i));
		}
		m_stateManager->Options = false;
	}
	else if (m_stateManager->MainMenu)
	{
		for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->size(); i++)
		{
			m_systemManager->renderSystem->RemoveEntity(m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->ID());
		}
		m_systemManager->menuSystem->ChangeMenu("MainMenu");
		for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->size(); i++)
		{
			m_systemManager->renderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i));
		}
		m_stateManager->MainMenu = false;
	}
}
