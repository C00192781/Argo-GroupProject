#include "ButtonSystem.h"

ButtonSystem::ButtonSystem(EventListener * e)
{
	m_eventListener = e;
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
		else
		{
			m_buttonComponents.at(i)->Selected(false);
		}

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
