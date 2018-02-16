#include "ShopInstance.h"



ShopInstance::ShopInstance(SystemManager* s)
{
	m_systemManager = s;
}

ShopInstance::~ShopInstance()
{
}

void ShopInstance::Generate(int luck)
{
	m_entities.push_back(new Entity("Item1Button"));
	SpriteComponent * sprite = new SpriteComponent("Button", 4, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 100, 50 + 74 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("ComicSans", "Buy", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("Item1"));
	sprite = new SpriteComponent("Plate", 4, 0, 0, 0, 64, 32, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 100 }));
	m_entities.back()->AddComponent(new TextComponent("ComicSans", "Buy", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("Item2Button"));
	sprite = new SpriteComponent("Button", 4, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 100, 274 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("ComicSans", "Buy", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("Item2"));
	sprite = new SpriteComponent("Plate", 4, 0, 0, 0, 64, 32, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 250 }));
	m_entities.back()->AddComponent(new TextComponent("ComicSans", "Buy", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("Item3Button"));
	sprite = new SpriteComponent("Button", 4, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 100, 424 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("ComicSans", "Buy", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("Item3"));
	sprite = new SpriteComponent("Plate", 4, 0, 0, 0, 64, 32, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 400 }));
	m_entities.back()->AddComponent(new TextComponent("ComicSans", "Buy", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	Load();
}
void ShopInstance::Load()
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