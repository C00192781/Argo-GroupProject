#include "TownInstance.h"



TownInstance::TownInstance(SystemManager * sys, EventListener * e)
{
	m_systemManager = sys;
	m_eventListener = e;
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
	m_entities.back()->AddComponent(new TextComponent("munro", "Shop", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("RumourButton"));
	sprite = new SpriteComponent("Button", 4, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 100, 250 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("munro", "Rumour", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("LeaveButton"));
	sprite = new SpriteComponent("Button", 4, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 100, 350 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("munro", "Leave", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

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
	for (int i = 0; i < m_entities.size(); i++)
	{

		Entity* player = m_systemManager->collisionSystem->FindEntity("Player", 3);

		player->Active(false);

		Entity* player2 = m_systemManager->collisionSystem->FindEntity("Player", 2);

		player2->Active(false);


		Entity* player3 = m_systemManager->collisionSystem->FindEntity("Player", 1);

		player3->Active(false);


		Entity* player4 = m_systemManager->collisionSystem->FindEntity("Player", 0);

		player4->Active(false);


		if (m_entities.at(i)->ID() == "ShopButton" && static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated())
		{
			m_eventListener->TownToShop = true;
			static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated(false);
		}
		if (m_entities.at(i)->ID() == "LeaveButton" && static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated())
		{
			m_eventListener->TownToWorld = true;
			static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated(false);
		}
		if (m_entities.at(i)->ID() == "RumourButton" && static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated())
		{
			int number_of_lines = 1;

			// a vector to hold all the indices: 0 to number_of_lines
			std::vector<int> line_indices(number_of_lines);
			std::iota(begin(line_indices), end(line_indices), 0); // init line_indices

																  // C++11 random library (should be preferred over rand()/srand())
			std::random_device r;
			std::seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() };
			std::mt19937 eng(seed);

			// shuffle the line_indices:
			std::shuffle(begin(line_indices), end(line_indices), eng);

			int number_of_lines_to_select = 1;
			assert(number_of_lines_to_select <= number_of_lines);

			std::string line;
			std::ifstream file("Rumours.txt");

			int line_number = 0;
			while (std::getline(file, line))
			{

				for (int i = 0; i < number_of_lines_to_select; ++i)
				{
					if (line_number == line_indices[i]) {
						std::cout << line << '\n';

					}
				}
				++line_number;
			}
		}
		static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated(false);
	}
}

