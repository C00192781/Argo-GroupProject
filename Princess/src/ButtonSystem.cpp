#include "ButtonSystem.h"


ButtonSystem::ButtonSystem(EventListener * e)
{

	m_eventListener = e;
	m_entities.push_back(new Entity("Null"));
	delete m_entities.back();
	m_entities.clear();
}

ButtonSystem::~ButtonSystem()
{
}

void ButtonSystem::Update()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	for (int i = 0; i < m_entities.size(); i++)
	{
		//std::cout << x << "," << y << std::endl;
		SDL_Rect holderA = m_buttonComponents.at(i)->Rect();
		holderA.x = m_positionComponents.at(i)->getX();
		holderA.y = m_positionComponents.at(i)->getY();
		SDL_Rect holderB{ x, y, 1, 1 };
		SDL_Rect holderC{ 0,0,0,0 };
		if (SDL_IntersectRect(&holderA, &holderB, &holderC))
		{
			m_buttonComponents.at(i)->Selected(true);
			if (m_eventListener->LeftClick)
			{
				m_buttonComponents.at(i)->Activated(true);
				m_buttonComponents.at(i)->Timer(5);
				m_spriteComponents.at(i)->Direction(2);
				m_buttonComponents.at(i)->Activated(true);
			}
		}

		//if (m_buttonComponents.at(3)->Activated()) //leave
		//{
		//	m_eventListener->TownToWorld = true;
		//
		//	for (int i = 0; i < m_buttonComponents.size(); i++)
		//	{ 
		//	//deactivate buttons somehow
		//	}
		//
		//}
		//
		////if (m_buttonComponents.at(2)->Activated()) //rumour
		////{
		////
		////
		////	int number_of_lines = 1;
		////
		////	// a vector to hold all the indices: 0 to number_of_lines
		////	std::vector<int> line_indices(number_of_lines);
		////	std::iota(begin(line_indices), end(line_indices), 0); // init line_indices
		////
		////														  // C++11 random library (should be preferred over rand()/srand())
		////	std::random_device r;
		////	std::seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() };
		////	std::mt19937 eng(seed);
		////
		////	// shuffle the line_indices:
		////	std::shuffle(begin(line_indices), end(line_indices), eng);
		////
		////	int number_of_lines_to_select = 1;
		////	assert(number_of_lines_to_select <= number_of_lines);
		////
		////	std::string line;
		////	std::ifstream file("Rumours.txt");
		////
		////	int line_number = 0;


		////	while (std::getline(file, line))
		////	{
		////
		////		for (int i = 0; i < number_of_lines_to_select; ++i)
		////		{
		////			if (line_number == line_indices[i]) {
		////				std::cout << line << '\n';
		////			}
		////		}
		////		++line_number;
		////	}
		////
		////
		////}

		//else
		//{
		//	m_buttonComponents.at(i)->Selected(false);
		//}

		if (m_buttonComponents.at(i)->Timer() <= 0 && m_buttonComponents.at(i)->Activated())
		{
			m_buttonComponents.at(i)->Activated(false);
			std::cout << "BUTTON UNPRESSED" << std::endl;
		}
		else
		{
			m_buttonComponents.at(i)->Timer(m_buttonComponents.at(i)->Timer() - 1);
		}

		if (m_buttonComponents.at(i)->Activated())
		{
			m_spriteComponents.at(i)->Direction(2);
		}
		else if (m_buttonComponents.at(i)->Selected())
		{
			m_spriteComponents.at(i)->Direction(1);
		}
		else
		{
			m_spriteComponents.at(i)->Direction(0);
		}
	}
}

void ButtonSystem::LoadComponent()
{
	int pcKey = -1;
	for (int j = 0; j < m_entities.back()->GetComponents()->size(); j++)
	{
		if (m_entities.back()->GetComponents()->at(j)->Type() == "ButtonC")
		{
			m_buttonComponents.push_back(static_cast<ButtonComponent*>(m_entities.back()->GetComponents()->at(j)));
		}
		else if (m_entities.back()->GetComponents()->at(j)->Type() == "PC")
		{
			m_positionComponents.push_back(static_cast<PositionComponent*>(m_entities.back()->GetComponents()->at(j)));
		}
		else if (m_entities.back()->GetComponents()->at(j)->Type() == "SC")
		{
			m_spriteComponents.push_back(static_cast<SpriteComponent*>(m_entities.back()->GetComponents()->at(j)));
		}
	}
}

void ButtonSystem::UnloadComponent(int x)
{
	m_buttonComponents.erase(m_buttonComponents.begin() + x);
	m_buttonComponents.shrink_to_fit();
	m_positionComponents.erase(m_positionComponents.begin() + x);
	m_positionComponents.shrink_to_fit();
	m_spriteComponents.erase(m_spriteComponents.begin() + x);
	m_spriteComponents.shrink_to_fit();
}
