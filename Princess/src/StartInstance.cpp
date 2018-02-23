#include "StartInstance.h"

StartInstance::StartInstance(SystemManager * sm, StateManager * s)
{
	m_id = "Start";
	m_systemManager = sm;
	m_stateManager = s;

}

StartInstance::~StartInstance()
{

}

void StartInstance::Generate()
{

//	m_active = true;
//
//	m_systemManager->controlSystem->Active(false);
//	m_systemManager->renderSystem->Camera(false);
//
//	m_systemManager->controlSystem->FindEntity("Player")->Active(false);
//	m_systemManager->renderSystem->FindEntity("Player")->Active(false);
//
//	for (int i = 0; i < m_entities.size(); i++)
//	{
//		delete m_entities.at(i);
//	}
//	m_entities.clear();
//	m_entities.shrink_to_fit();
//	m_systemManager->controlSystem->SelectiveClear();
//	m_systemManager->renderSystem->SelectiveClear();
//	m_systemManager->movementSystem->SelectiveClear();
//
//	m_systemManager->menuSystem->SetUpOptionsMenu();
//	m_systemManager->menuSystem->SetUpMainMenu();
//	m_systemManager->menuSystem->ChangeMenu("MainMenu");
//	for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->size(); i++)
//	{
//		if (m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->FindComponent("TextComponent") != nullptr)
//		{
//			m_systemManager->textRenderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i));
//		}
//		if (m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->FindComponent("SC") != nullptr)
//		{
//			m_systemManager->renderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i));
//		}
//	}
//	if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu") != nullptr)
//	{
//		for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->size(); i++)
//		{
//			if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->ID() == "SoundText")
//			{
//				if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("TextComponent") != nullptr)
//				{
//					std::string text;
//					text = "Sound :";
//					text += std::to_string(m_systemManager->soundSystem->GetSoundVolume());
//					text += "%";
//					static_cast<TextComponent*>(m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("TextComponent"))->Text(text);
//				}
//				
//			}
//			if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->ID() == "MusicText")
//			{
//				if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("TextComponent") != nullptr)
//				{
//					std::string text;
//					text = "Music :";
//					text += std::to_string(m_systemManager->soundSystem->GetMusicVolume());
//					text += "%";
//					static_cast<TextComponent*>(m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("TextComponent"))->Text(text);
//				}
//
//			}
//		}
//	}
//
//}
//
//void StartInstance::Update()
//{
//	if (m_stateManager->Options)
//	{
//		for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->size(); i++)
//		{
//			if (m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->FindComponent("TextComponent") != nullptr)
//			{
//				m_systemManager->textRenderSystem->RemoveEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->ID());
//			}
//			if (m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->FindComponent("SC") != nullptr)
//			{
//				m_systemManager->renderSystem->RemoveEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->ID());
//			}
//		}
//		m_systemManager->menuSystem->ChangeMenu("OptionsMenu");
//		for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->size(); i++)
//		{
//			if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("TextComponent") != nullptr)
//			{
//				m_systemManager->textRenderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i));
//			}
//			if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("SC") != nullptr)
//			{
//				m_systemManager->renderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i));
//			}
//		}
//		m_stateManager->Options = false;
//	}
//	else if (m_stateManager->MainMenu)
//	{
//		for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->size(); i++)
//		{
//			if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("TextComponent") != nullptr)
//			{
//				m_systemManager->textRenderSystem->RemoveEntity(m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->ID());
//			}
//			if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("SC") != nullptr)
//			{
//				m_systemManager->renderSystem->RemoveEntity(m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->ID());
//			}
//		}
//		m_systemManager->menuSystem->ChangeMenu("MainMenu");
//		for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->size(); i++)
//		{
//			if (m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->FindComponent("TextComponent") != nullptr)
//			{
//				m_systemManager->textRenderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i));
//			}
//			if (m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i)->FindComponent("SC") != nullptr)
//			{
//				m_systemManager->renderSystem->AddEntity(m_systemManager->menuSystem->GetMenuComponent("MainMenu")->Buttons()->at(i));
//			}
//		}
//		m_stateManager->MainMenu = false;
//	}
//	if (m_stateManager->increaseSound || m_stateManager->decreaseSound)
//	{
//		if (m_stateManager->increaseSound)
//		{
//			if (m_systemManager->soundSystem->GetSoundVolume() < 100)
//			{
//				m_systemManager->soundSystem->SetSoundVolume(m_systemManager->soundSystem->GetSoundVolume() + 10);
//			}
//		}
//		if (m_stateManager->decreaseSound)
//		{
//			if (m_systemManager->soundSystem->GetSoundVolume() > 0)
//			{
//				m_systemManager->soundSystem->SetSoundVolume(m_systemManager->soundSystem->GetSoundVolume() - 10);
//			}
//		}
//		if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu") != nullptr)
//		{
//			for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->size(); i++)
//			{
//				if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->ID() == "SoundText")
//				{
//					if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("TextComponent") != nullptr)
//					{
//						std::string text;
//						text = "Sound :";
//						text += std::to_string(m_systemManager->soundSystem->GetSoundVolume());
//						text += "%";
//						static_cast<TextComponent*>(m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("TextComponent"))->Text(text);
//					}
//					break;
//				}
//			}
//		}
//		m_stateManager->increaseSound = false;
//		m_stateManager->decreaseSound = false;
//	}
//	if (m_stateManager->increaseMusic || m_stateManager->decreaseMusic)
//	{
//		if (m_stateManager->increaseMusic)
//		{
//			if (m_systemManager->soundSystem->GetMusicVolume() < 100)
//			{
//				m_systemManager->soundSystem->SetMusicVolume(m_systemManager->soundSystem->GetMusicVolume() + 10);
//			}
//		}
//		if (m_stateManager->decreaseMusic)
//		{
//			if (m_systemManager->soundSystem->GetMusicVolume() > 0)
//			{
//				m_systemManager->soundSystem->SetMusicVolume(m_systemManager->soundSystem->GetMusicVolume() - 10);
//			}
//		}
//		if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu") != nullptr)
//		{
//			for (int i = 0; i < m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->size(); i++)
//			{
//				if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->ID() == "MusicText")
//				{
//					if (m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("TextComponent") != nullptr)
//					{
//						std::string text;
//						text = "Music :";
//						text += std::to_string(m_systemManager->soundSystem->GetMusicVolume());
//						text += "%";
//						static_cast<TextComponent*>(m_systemManager->menuSystem->GetMenuComponent("OptionsMenu")->Buttons()->at(i)->FindComponent("TextComponent"))->Text(text);
//					}
//					break;
//				}
//			}
//		}
//		m_stateManager->increaseMusic = false;
//		m_stateManager->decreaseMusic = false;
//	}
//	if (m_stateManager->StartGame)
//	{
//		m_systemManager->controlSystem->FindEntity("Player")->Active(true);
//		m_systemManager->renderSystem->FindEntity("Player")->Active(true);
//		m_systemManager->renderSystem->Camera(true);
//		m_systemManager->controlSystem->Active(true);
//		m_systemManager->menuSystem->Active(false);
//
//	}
}


