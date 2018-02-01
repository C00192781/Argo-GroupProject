#include "MovementSystem.h"

void MovementSystem::Update() 
{
	int mcKey = -1;
	int pcKey = -1;

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
}