#include "MovementSystem.h"

void MovementSystem::Update(float deltaTime)
{
	SDL_GetMouseState(&m_mouseX, &m_mouseY);

	// looks for if there is a position and movement component in the entity
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->Active())
		{
			float* xPos = m_positionComponent.at(i)->getXRef();
			float* yPos = m_positionComponent.at(i)->getYRef();
		
			*xPos += m_movementComponent.at(i)->getXVelocity() * deltaTime;
			*yPos += m_movementComponent.at(i)->getYVelocity() * deltaTime;
		
			m_collisionComponent.at(i)->setPosition(*xPos, *yPos);
		
			if (m_entities.at(i)->ID() == "Player")
			{
				if (m_movementComponent.at(i)->getLockedOrientation() == false)
				{
					m_movementComponent.at(i)->setOrientation((atan2((float)m_mouseY - (m_windowHeight / 2), (float)m_mouseX - (m_windowWidth / 2))) * (180 / 3.142) + 90);
				}
			}
		}
	}
}

void MovementSystem::LoadComponent()
{
	int pcKey = -1;
	int movementKey = -1;
	int collisionKey = -1;

	for (int j = 0; j < m_entities.back()->GetComponents()->size(); j++)
	{
		if (m_entities.back()->GetComponents()->at(j)->Type() == "PC")
		{
			pcKey = j;
		}
		else if (m_entities.back()->GetComponents()->at(j)->Type() == "movement")
		{
			movementKey = j;
		}
		else if (m_entities.back()->GetComponents()->at(j)->Type() == "collision")
		{
			collisionKey = j;
		}
		if (movementKey >= 0 && pcKey >= 0 && collisionKey >= 0)
		{
			break;
		}
	}
	m_positionComponent.push_back(static_cast<PositionComponent*>(m_entities.back()->GetComponents()->at(pcKey)));
	m_movementComponent.push_back(static_cast<MovementComponent*>(m_entities.back()->GetComponents()->at(movementKey)));
	m_collisionComponent.push_back(static_cast<CollisionComponent*>(m_entities.back()->GetComponents()->at(collisionKey)));
}

void MovementSystem::UnloadComponent(int x)
{
	m_positionComponent.erase(m_positionComponent.begin() + x);
	m_movementComponent.erase(m_movementComponent.begin() + x);
	m_collisionComponent.erase(m_collisionComponent.begin() + x);
	m_positionComponent.shrink_to_fit();
	m_movementComponent.shrink_to_fit();
	m_collisionComponent.shrink_to_fit();
}