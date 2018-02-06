#include "ControlSystem.h"
#include <iostream>

void ControlSystem::Update() 
{
	for (int i = 0; i < m_entities.size(); i++) 
	{
		int mcKey = -1;
		int pjKey = -1;
		int acKey = -1;

		// looks for if there is a movement component in the entity
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "movement")
				{
					mcKey = j;
				}
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PJ")
				{
					pjKey = j;
				}
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "AC")
				{
					acKey = j;
				}
			}
		}

		// makes sure it finds a movement component in the entity
		if (mcKey >= 0) 
		{
			SDL_Point holder{ 0, 0 };
			int speed = static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->MovementSpeed();

			if (m_eventListener->W)
			{
				holder.y = -speed;
			}
			if (m_eventListener->A)
			{
				holder.x = -speed;
			}
			if (m_eventListener->S)
			{
				holder.y = speed;
			}
			if (m_eventListener->D)
			{
				holder.x = speed;
			}

			static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setVelocity(holder);
		}
		if (pjKey >= 0)
		{
			if (m_eventListener->Space)
			{
				
			}
		}
	}
}