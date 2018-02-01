#include "ControlSystem.h"
#include <iostream>

void ControlSystem::Update() 
{
	for (int i = 0; i < m_entities.size(); i++) 
	{
		int pcKey = -1;
		int mcKey = -1;

		// looks for if there is a position and control component in the entity
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++) 
		{
			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC")
				{
					pcKey = j;
				}
				else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "movement")
				{
					mcKey = j;
				}
			}
		}

		// makes sure it finds the position in the vector of the position and control components
		if (pcKey >= 0 && mcKey >= 0) 
		{
			updateVelocity(i, mcKey);
			updatePosition(i, mcKey, pcKey);
		}
	}
}

void ControlSystem::updatePosition(int entityIndex, int mcKey, int pcKey)
{
	SDL_Point position = static_cast<PositionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(pcKey))->getPosition();
	SDL_Point velocity = static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->getVelocity();

	position.x += velocity.x;
	position.y += velocity.y;

	static_cast<PositionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(pcKey))->setPosition(position);
}

void ControlSystem::updateVelocity(int entityIndex, int mcKey)
{
	SDL_Point holder{ 0, 0 };
	int speed = static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->getSpeed();

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

	static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setVelocity(holder);
}