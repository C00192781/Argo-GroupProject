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
	if (timer > 3)
	{
		//Do Next
		m_systemManager->renderSystem->Camera(true);
		m_systemManager->healthSystem->Active(true);
		m_systemManager->controlSystem->Active(true);
		m_systemManager->controlSystem->FindEntity("Player")->Active(true);
		m_systemManager->renderSystem->FindEntity("Player")->Active(true);
		m_stateManager->LoadGame = true;
		m_stateManager->ReturnToWorld = true;
		timer = 0;
		for (int i = 0; i < m_entities.size(); i++)
		{
			m_entities.at(i)->Active(false);
		}
	}
}

void GameOverInstance::Generate()
{


	m_systemManager->controlSystem->Active(false);
	//m_systemManager->renderSystem->Camera(false);
	//m_systemManager->collisionSystem->Active(false);
	m_systemManager->healthSystem->Active(false);
	m_systemManager->textRenderSystem->Active(true);

	m_systemManager->controlSystem->FindEntity("Player")->Active(false);
	m_systemManager->renderSystem->FindEntity("Player")->Active(false);
	for (int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities.at(i);
	}

	m_entities.clear();
	m_entities.shrink_to_fit();
	m_systemManager->controlSystem->SelectiveClear();
	m_systemManager->renderSystem->SelectiveClear();
	m_systemManager->movementSystem->SelectiveClear();
	m_systemManager->collisionSystem->SelectiveClear();
	m_systemManager->aiSystem->SelectiveClear();
	m_systemManager->textRenderSystem->SelectiveClear();

	Entity * gameOverText = new Entity("GameOverText");
	gameOverText->AddComponent(new PositionComponent(SDL_Point{ 325, 125 }));
	gameOverText->AddComponent(new TextComponent("ComicSans", "GAME OVER", SDL_Color{ 255,255,255,0 }, 64 * 3, 16 * 3));
	m_entities.push_back(gameOverText);
	m_systemManager->textRenderSystem->AddEntity(m_entities.at(m_entities.size() - 1));
}
