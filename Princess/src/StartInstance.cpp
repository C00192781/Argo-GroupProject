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
		if (m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->FindComponent("TextComponent") != nullptr)
		{
			m_systemManager->textRenderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i));
		}
		if (m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->FindComponent("SC") != nullptr)
		{
			m_systemManager->renderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i));
		}
	}
}

void StartInstance::Update()
{
	if (m_stateManager->Options)
	{
		for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->size(); i++)
		{
			if (m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->FindComponent("TextComponent") != nullptr)
			{
				m_systemManager->textRenderSystem->RemoveEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->ID());
			}
			if (m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->FindComponent("SC") != nullptr)
			{
				m_systemManager->renderSystem->RemoveEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->ID());
			}
		}
		m_systemManager->menuSystem->ChangeMenu("OptionsMenu");
		for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->size(); i++)
		{
			if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("TextComponent") != nullptr)
			{
				m_systemManager->textRenderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i));
			}
			if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("SC") != nullptr)
			{
				m_systemManager->renderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i));
			}
		}
		m_stateManager->Options = false;
	}
	else if (m_stateManager->MainMenu)
	{
		for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->size(); i++)
		{
			if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("TextComponent") != nullptr)
			{
				m_systemManager->textRenderSystem->RemoveEntity(m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->ID());
			}
			if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("SC") != nullptr)
			{
				m_systemManager->renderSystem->RemoveEntity(m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->ID());
			}
		}
		m_systemManager->menuSystem->ChangeMenu("MainMenu");
		for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->size(); i++)
		{
			if (m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->FindComponent("TextComponent") != nullptr)
			{
				m_systemManager->textRenderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i));
			}
			if (m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->FindComponent("SC") != nullptr)
			{
				m_systemManager->renderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i));
			}
		}
		m_stateManager->MainMenu = false;
	}
	if (m_stateManager->increaseSound || m_stateManager->decreaseSound)
	{
		if (m_stateManager->increaseSound)
		{
			if (m_systemManager->soundSystem->GetSoundVolume() < 100)
			{
				m_systemManager->soundSystem->SetSoundVolume(m_systemManager->soundSystem->GetSoundVolume() + 10);
			}
		}
		if (m_stateManager->decreaseSound)
		{
			if (m_systemManager->soundSystem->GetSoundVolume() > 0)
			{
				m_systemManager->soundSystem->SetSoundVolume(m_systemManager->soundSystem->GetSoundVolume() - 10);
			}
		}
		if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu") != nullptr)
		{
			for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->size(); i++)
			{
				if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->ID() == "SoundText")
				{
					if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("TextComponent") != nullptr)
					{
						std::string text;
						text = "Sound :";
						text += std::to_string(m_systemManager->soundSystem->GetSoundVolume());
						text += "%";
						static_cast<TextComponent*>(m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("TextComponent"))->Text(text);
					}
					break;
				}
			}
		}
		m_stateManager->increaseSound = false;
		m_stateManager->decreaseSound = false;
	}
}


