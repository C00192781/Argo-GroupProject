#include "MovementSystem.h"

void MovementSystem::Update()
{
	// looks for if there is a position and movement component in the entity
	for (int i = 0; i < m_entities.size(); i++)
	{
		int mcKey = -1;
		int rectangleKey = -1;

		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "rectangle")
			{
				rectangleKey = j;
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "movement")
			{
				mcKey = j;
			}
		}

		// makes sure it finds a position and movement component in the entity
		if (mcKey >= 0 && rectangleKey >= 0)
		{
			SDL_Point position = static_cast<RectangleComponent*>(m_entities.at(i)->GetComponents()->at(rectangleKey))->getPosition();
			SDL_Point velocity = static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getVelocity();

			position.x += velocity.x;
			position.y += velocity.y;

			static_cast<RectangleComponent*>(m_entities.at(i)->GetComponents()->at(rectangleKey))->setPosition(position);
		}
	}
}
