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
	m_entities.back()->AddComponent(new TextComponent("munro", "Princess C'est Douce", SDL_Color{ 255,255,255,255 }, 9999 * 3, 16 * 3));
	Load();
}

MenuInstance::MenuInstance(SystemManager* s, EventListener * listener, StateManager * states, std::vector<Entity*> players)
{
	m_systemManager = s;
	m_eventListener = listener;
	m_stateManager = states;
	m_players = players;

	m_entities.push_back(new Entity("PlayButton"));
	SpriteComponent * sprite = new SpriteComponent("Button", 3, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 350, 150 + 74 }));
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


	Entity* player = m_systemManager->collisionSystem->FindEntity("Player", 3);

	player->Active(false);

	Entity* player2 = m_systemManager->collisionSystem->FindEntity("Player", 2);

	player2->Active(false);


	Entity* player3 = m_systemManager->collisionSystem->FindEntity("Player", 1);

	player3->Active(false);


	Entity* player4 = m_systemManager->collisionSystem->FindEntity("Player", 0);

	player4->Active(false);

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

				m_players.at(3)->Control(true);
				m_systemManager->controlSystem->AddEntity(m_players.at(3));
				m_players.at(0)->Active(true);

				for (int i = 0; i < m_players.size() - 1; i++)
				{
					m_players.at(i)->AddComponent(new AiLogicComponent());
					m_players.at(i)->AddComponent(new SeekComponent());
				}
			}
			if (m_entities.at(i)->ID() == "JoinButton" && static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated())
			{
				connect();

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

void MenuInstance::connect()
{
	if (m_systemManager->networkSystem->connectToServer())
	{
		m_systemManager->networkSystem->init();
		srand(m_systemManager->networkSystem->getServerSeed());
		m_systemManager->networkSystem->Active(true);

		if (m_systemManager->networkSystem->getID() == 0)
		{
			m_systemManager->networkSystem->setHost(true);
		}
		m_eventListener->MenuToWorld = true;
		m_eventListener->host = m_systemManager->networkSystem->getHost();
		m_eventListener->connected = m_systemManager->networkSystem->getConnected();

		NetworkIDComponent* n = nullptr;
		for (int i = 0; i < m_players.size(); i++)
		{
			n = static_cast<NetworkIDComponent*>(m_players.at(i)->FindComponent("network"));

			if (m_systemManager->networkSystem->getID() == n->getID())
			{
				m_players.at(i)->Control(true);
				m_systemManager->controlSystem->AddEntity(m_players.at(i));
				m_players.at(i)->Active(true);
				break;
			}
		}
	}
	else
	{
		std::cout << "Failed to connect" << std::endl;
		srand(time(NULL));
		m_systemManager->networkSystem->Active(false);
		m_eventListener->host = m_systemManager->networkSystem->getHost();
		m_eventListener->connected = m_systemManager->networkSystem->getConnected();
	}
}

void MenuInstance::LoadComponent()
{

}

void MenuInstance::UnloadComponent(int x)
{

}