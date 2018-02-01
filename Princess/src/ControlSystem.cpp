#include "ControlSystem.h"
#include <iostream>

void ControlSystem::Update() 
{
	for (int i = 0; i < m_entities.size(); i++) 
	{
		int pcKey = -1;
		int ccKey = -1;
		int mcKey = -1;

		if (m_eventListener->LeftClick)
		{
			std::cout << "I AM DETECTING LEFT" << std::endl;
		}


		// looks for if there is a position and control component in the entity
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++) 
		{
			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC")
				{
					pcKey = j;
				}
				else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "control")
				{
					ccKey = j;
				}
				else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "movement")
				{
					mcKey = j;
				}
			}
		}

		// makes sure it finds the position in the vector of the position and control components
		if (pcKey >= 0 && ccKey >= 0 && mcKey >= 0) 
		{
			//SDL_Point holder = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition();
			
			//static_cast<ControlComponent*>(m_entities.at(i)->GetComponents()->at(ccKey))->getInput()->handleInput(*e, holder);
			
			//static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->setPosition(holder);

			//SDL_Point holder = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition();


		}
	}
}

void ControlSystem::updateVelocity(SDL_Event *e, int entityIndex, int ccKey, int mcKey)
{
	SDL_Point holder = static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->getVelocity();

	//static_cast<ControlComponent*>(m_entities.at(entityIndex)->GetComponents()->at(ccKey))->getInput()->handleInput(*e, holder);

	static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setVelocity(holder);
}