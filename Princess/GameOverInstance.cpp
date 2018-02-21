#include "GameOverInstance.h"

GameOverInstance::GameOverInstance(SystemManager * sm, StateManager * s)
{
	m_systemManager = sm;
	m_stateManager = s;
	hasFaded = false;
}

GameOverInstance::~GameOverInstance()
{

}

void GameOverInstance::Update(float deltaTime)
{
	timer += deltaTime;
	if (deltaTime > 3)
	{
		//Do Next
		timer = 0;
	}
}

void GameOverInstance::Generate()
{
	m_systemManager->menuSystem->Active(true);
	m_systemManager->controlSystem->Active(false);
	m_systemManager->renderSystem->Camera(false);

	m_systemManager->controlSystem->FindEntity("Player")->Active(false);
	m_systemManager->renderSystem->FindEntity("Player")->Active(false);

	for (int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities.at(i);
	}

	m_entities.clear();
	m_entities.shrink_to_fit();
	m_systemManager->textRenderSystem->SelectiveClear();

	Entity * gameOverText = new Entity("GameOverText");
	gameOverText->AddComponent(new PositionComponent(SDL_Point{ 325, 125 }));
	gameOverText->AddComponent(new TextComponent("ComicSans", "GAME OVER", SDL_Color{ 255,255,255,0 }, 64 * 3, 16 * 3));
	m_entities.push_back(gameOverText);
	m_systemManager->textRenderSystem->AddEntity(m_entities.at(m_entities.size() - 1));
}
