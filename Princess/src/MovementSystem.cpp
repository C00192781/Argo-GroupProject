#include "MovementSystem.h"

void MovementSystem::Update()
{
	// looks for if there is a position and movement component in the entity
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->Active())
		{
			int mcKey = -1;
			int pcKey = -1;
			bool skip = false;

			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC")
				{
					pcKey = j;
				}
				else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "movement")
				{
					mcKey = j;
					if (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getVelocity().x == 0 && static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getVelocity().y == 0)
					{
						skip = true;
						break;
					}
				}
				if (pcKey >= 0 && mcKey >= 0)
				{
					break;
				}
			}

			// makes sure it finds a position and movement component in the entity
			if (mcKey >= 0 && pcKey >= 0 && !skip)
			{
				SDL_Point position = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition();
				SDL_Point velocity = static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getVelocity();

				position.x += velocity.x;
				position.y += velocity.y;

				static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->setPosition(position);
			}
		}
	}
}
