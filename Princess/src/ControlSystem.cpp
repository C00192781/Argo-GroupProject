#include "ControlSystem.h"
#include <iostream>

void ControlSystem::Update() 
{
	for (int i = 0; i < m_entities.size(); i++) 
	{
		int mcKey = -1;

		// looks for if there is a movement component in the entity
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "movement")
				{
					mcKey = j;
				}
			}
		}

		// makes sure it finds a movement component in the entity
		if (mcKey >= 0) 
		{
			SDL_Point holder{ 0, 0 };
			int speed = static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getSpeed();

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

			//updatePosition(i, mcKey, pcKey);
		}
	}
}

//void ControlSystem::updatePosition(int entityIndex, int mcKey, int pcKey)
//{
//	SDL_Point position = static_cast<PositionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(pcKey))->getPosition();
//	SDL_Point velocity = static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->getVelocity();
//
//	position.x += velocity.x;
//	position.y += velocity.y;
//
//	static_cast<PositionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(pcKey))->setPosition(position);
//}