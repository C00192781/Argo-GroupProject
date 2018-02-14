#include "TownInstance.h"



TownInstance::TownInstance(SystemManager * sys)
{
	m_systemManager = sys;
}

TownInstance::~TownInstance()
{

}

void TownInstance::Generate(std::string type)
{
	m_entities.push_back(new Entity("ShopButton"));
	SpriteComponent * sprite = new SpriteComponent("Button", 4, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 100, 50 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("ComicSans", "Shop", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("RestButton"));
	sprite = new SpriteComponent("Button", 4, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 100, 150 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("ComicSans", "Rest", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("RumourButton"));
	sprite = new SpriteComponent("Button", 4, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 100, 250 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("ComicSans", "Rumour", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("LeaveButton"));
	sprite = new SpriteComponent("Button", 4, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 100, 350 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("ComicSans", "Leave", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_systemManager->renderSystem->SelectiveClear();
	m_systemManager->buttonSystem->SelectiveClear();
	m_systemManager->textRenderSystem->SelectiveClear();

	for (int i = 0; i < m_entities.size(); i++)
	{
		m_systemManager->renderSystem->AddEntity(m_entities.at(i));
		m_systemManager->buttonSystem->AddEntity(m_entities.at(i));
		m_systemManager->textRenderSystem->AddEntity(m_entities.at(i));
	}
}

void TownInstance::Load()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		m_systemManager->renderSystem->AddEntity(m_entities.at(i));
		m_systemManager->buttonSystem->AddEntity(m_entities.at(i));
		m_systemManager->textRenderSystem->AddEntity(m_entities.at(i));
	}
}

void TownInstance::Update()
{

}