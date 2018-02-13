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
	m_systemManager->ControlSystem->SelectiveClear();
	m_systemManager->RenderSystem->SelectiveClear();
	m_systemManager->MovementSystem->SelectiveClear();
	m_systemManager->AiSystem->SelectiveClear();
	m_systemManager->healthSystem->SelectiveClear();
	m_systemManager->menuSystem->SelectiveClear();
	delete m_factory;

	m_systemManager->menuSystem->SetUpMainMenu();
	m_systemManager->menuSystem->SetUpOptionsMenu();
	m_systemManager->menuSystem->ChangeMenu("MainMenu");
	for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->size(); i++)
	{
		m_systemManager->RenderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i));
	}
}

void StartInstance::Update()
{
	if (m_stateManager->Options)
	{
		m_systemManager->menuSystem->ChangeMenu("OptionsMenu");
		for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->size(); i++)
		{
			m_systemManager->RenderSystem->RemoveEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->ID());
		}
		for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->size(); i++)
		{
			m_systemManager->RenderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i));
		}
	}
	else if (m_stateManager->MainMenu)
	{
		m_systemManager->menuSystem->ChangeMenu("MainMenu");
		for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->size(); i++)
		{
			m_systemManager->RenderSystem->RemoveEntity(m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->ID());
		}
		for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->size(); i++)
		{
			m_systemManager->RenderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i));
		}
	}
}
