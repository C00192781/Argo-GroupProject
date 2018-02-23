#include "OptionsInstance.h"



OptionsInstance::OptionsInstance(SystemManager* s, EventListener * listener, StateManager * states)
{
	m_systemManager = s;
	m_eventListener = listener;
	m_stateManager = states;

	m_entities.push_back(new Entity("VolumnUp"));
	SpriteComponent * sprite = new SpriteComponent("Button", 3, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 250, 150 + 74 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("munro", "Vol +", SDL_Color{ 255,255,255,255 }, 32 * 3, 9999));

	m_entities.push_back(new Entity("VolumnDown"));
	sprite = new SpriteComponent("Button", 3, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 550, 150 + 74 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("munro", "Vol -", SDL_Color{ 255,255,255,255 }, 32 * 3, 9999));

	m_entities.push_back(new Entity("MusicUp"));
	sprite = new SpriteComponent("Button", 3, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 250, 250 + 74 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("munro", "Vol +", SDL_Color{ 255,255,255,255 }, 32 * 3, 9999));

	m_entities.push_back(new Entity("MusicDown"));
	sprite = new SpriteComponent("Button", 3, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 550, 250 + 74 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("munro", "Vol -", SDL_Color{ 255,255,255,255 }, 32 * 3, 9999));

	m_entities.push_back(new Entity("Exit"));
	sprite = new SpriteComponent("Button", 3, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 350, 350 + 74 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("munro", "Exit", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("Options Card"));
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 350, 50 + 74 }));
	m_entities.back()->AddComponent(new TextComponent("munro", "Options", SDL_Color{ 255,255,255,255 }, 9999 * 3, 16 * 3));

	m_entities.push_back(new Entity("% Sound Card"));
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 360, 150 + 74 }));
	m_entities.back()->AddComponent(new TextComponent("munro", "100%", SDL_Color{ 255,255,255,255 }, 9999 * 3, 16 * 3));

	m_entities.push_back(new Entity("% Music Card"));
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 360, 250 + 74 }));
	m_entities.back()->AddComponent(new TextComponent("munro", "100%", SDL_Color{ 255,255,255,255 }, 9999 * 3, 16 * 3));
	Load();
}

OptionsInstance::~OptionsInstance()
{

}

void OptionsInstance::Load()
{
	m_systemManager->renderSystem->SelectiveClear();
	m_systemManager->buttonSystem->SelectiveClear();
	m_systemManager->textRenderSystem->SelectiveClear();

	for (int i = 0; i < m_entities.size(); i++)
	{
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "SC")
			{
				m_systemManager->renderSystem->AddEntity(m_entities.at(i));
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "ButtonC")
			{
				m_systemManager->buttonSystem->AddEntity(m_entities.at(i));
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "TextComponent")
			{
				m_systemManager->textRenderSystem->AddEntity(m_entities.at(i));
			}
		}
	}
}

void OptionsInstance::Update()
{
	if (m_timer <= 0)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			if (m_entities.at(i)->ID() == "Exit" && static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated())
			{
				m_eventListener->OptionsToMenu = true;
				static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated(false);
				m_timer = 30;
			}
			if (m_entities.at(i)->ID() == "VolumnUp" && static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated())
			{
				m_systemManager->soundSystem->SetSoundVolume(m_systemManager->soundSystem->GetSoundVolume() + 10);
				static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated(false);
				m_timer = 30;
			}
			if (m_entities.at(i)->ID() == "VolumnDown" && static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated())
			{
				m_systemManager->soundSystem->SetSoundVolume(m_systemManager->soundSystem->GetSoundVolume() - 10);
				static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated(false);
				m_timer = 30;
			}
			if (m_entities.at(i)->ID() == "MusicUp" && static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated())
			{
				if (m_systemManager->soundSystem->GetMusicVolume() < 100)
				{
					m_systemManager->soundSystem->SetMusicVolume(m_systemManager->soundSystem->GetMusicVolume() + 10);
				}
				static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated(false);
				m_timer = 30;
			}
			if (m_entities.at(i)->ID() == "MusicDown" && static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated())
			{
				if (m_systemManager->soundSystem->GetMusicVolume()> 0)
				{
					m_systemManager->soundSystem->SetMusicVolume(m_systemManager->soundSystem->GetMusicVolume() - 10);
				}
				static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated(false);
				m_timer = 30;
			}
			if (m_entities.at(i)->ID() == "% Sound Card")
			{
				static_cast<TextComponent*>(m_entities.at(i)->FindComponent("TextComponent"))->Text("Sound " + std::to_string(m_systemManager->soundSystem->GetSoundVolume()));
			}
			if (m_entities.at(i)->ID() == "% Music Card")
			{
				static_cast<TextComponent*>(m_entities.at(i)->FindComponent("TextComponent"))->Text("Music "+std::to_string(m_systemManager->soundSystem->GetMusicVolume()));
			}
		}
	}
	else
	{
		m_timer--;
	}
}

void OptionsInstance::LoadComponent()
{

}

void OptionsInstance::UnloadComponent(int x)
{

}