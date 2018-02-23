#include "MenuInstance.h"

MenuInstance::MenuInstance(SystemManager* s, EventListener * listener, StateManager * states)
{
	m_systemManager = s;
	m_eventListener = listener;
	m_stateManager = states;

	m_entities.push_back(new Entity("PlayButton"));
	SpriteComponent * sprite = new SpriteComponent("Button", 3, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{350, 150 + 74 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("munro", "Play", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("JoinButton"));
	sprite = new SpriteComponent("Button", 3, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 350, 250 + 74 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("munro", "Join", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("OptionsButton"));
	sprite = new SpriteComponent("Button", 3, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 350, 350 + 74 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("munro", "Options", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("ExitButton"));
	sprite = new SpriteComponent("Button", 3, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 350, 450 + 74 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("munro", "Exit", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("TitleCard"));
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 280, 50 + 74 }));
	m_entities.back()->AddComponent(new TextComponent("munro", "Princess C'est Deus", SDL_Color{ 255,255,255,255 }, 9999 * 3, 16 * 3));
	Load();
}

MenuInstance::~MenuInstance()
{

}

void MenuInstance::Load()
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

void MenuInstance::Update()
{
	if (m_timer <= 0)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			if (m_entities.at(i)->ID() == "PlayButton" && static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated())
			{
				m_eventListener->MenuToWorld = true;
				static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated(false);
				m_timer = 30;
			}
			if (m_entities.at(i)->ID() == "OptionsButton" && static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated())
			{
				m_eventListener->MenuToOptions = true;
				static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated(false);
				m_timer = 30;
			}
		}
	}
	else
	{
		m_timer--;
	}
}

void MenuInstance::LoadComponent()
{

}

void MenuInstance::UnloadComponent(int x)
{

}