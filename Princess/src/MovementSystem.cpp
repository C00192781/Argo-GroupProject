#include "MovementSystem.h"

void MovementSystem::Update(float deltaTime)
{
	SDL_GetMouseState(&m_mouseX, &m_mouseY);

	// looks for if there is a position and movement component in the entity
	for (int i = 0; i < m_entities.size(); i++)
	{
		//int pcKey = -1;
		//int movementKey = -1;
		//int collisionKey = -1;
		//
		//for (int j = 0; j < m_entities.back()->GetComponents()->size(); j++)
		//{
		//	if (m_entities.back()->GetComponents()->at(j)->Type() == "PC")
		//	{
		//		pcKey = j;
		//	}
		//	else if (m_entities.back()->GetComponents()->at(j)->Type() == "movement")
		//	{
		//		movementKey = j;
		//	}
		//	else if (m_entities.back()->GetComponents()->at(j)->Type() == "collision")
		//	{
		//		collisionKey = j;
		//	}
		//	if (movementKey > 0 && pcKey > 0 && collisionKey > 0)
		//	{
		//		break;
		//	}
		//}
		//
		//if (movementKey > 0 && pcKey > 0 && collisionKey > 0)
		//{
		//	float* xPos = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getXRef();
		//	float* yPos = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getYRef();
		//
		//	*xPos += static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(movementKey))->getXVelocity() * deltaTime;
		//	*yPos += static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(movementKey))->getYVelocity() * deltaTime;
		//
		//	//static_cast<CollisionComponent*>(m_entities.at(i)->GetComponents()->at(collisionKey))->setPosition(*xPos, *yPos);
		//
		//	if (m_entities.at(i)->ID() == "Player")
		//	{
		//		if (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(movementKey))->getLockedOrientation() == false)
		//		{
		//			static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(movementKey))->setOrientation((atan2((float)m_mouseY - *yPos, (float)m_mouseX - *xPos)) * (180 / 3.142) + 90);
		//			//std::cout << m_movementComponent.at( << std::endl;
		//		}
		//	}
		//}

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
					//m_movementComponent.at(i)->setOrientation((atan2((float)m_mouseY - *yPos, (float)m_mouseX - *xPos)) * (180 / 3.142) + 90);
					m_movementComponent.at(i)->setOrientation((atan2(*yPos - ((float)m_mouseY / 2), *xPos - ((float)m_mouseY / 2))) * (180 / 3.142) + 90);
					//std::cout << "X Pos: " << *xPos << std::endl;
					//std::cout << "Y Pos: " << *yPos << std::endl;
					//std::cout << "Mouse X: " << m_mouseX + *xPos << std::endl;
					std::cout << "Mouse Y: " << m_mouseY << std::endl;
					//std::cout << "Orientation: " << m_movementComponent.at(i)->getOrientation() << std::endl;
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