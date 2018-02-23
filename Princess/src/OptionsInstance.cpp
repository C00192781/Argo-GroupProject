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
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 450, 150 + 74 }));
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

	m_entities.push_back(new Entity("% Card"));
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 360, 150 + 74 }));
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

}

void OptionsInstance::LoadComponent()
{

}

void OptionsInstance::UnloadComponent(int x)
{

}