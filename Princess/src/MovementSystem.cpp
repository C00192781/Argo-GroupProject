#include "MovementSystem.h"


void MovementSystem::LoadComponent()
{
	//int pcKey = -1;
	//int scKey = -1;
	//for (int j = 0; j < m_entities.back()->GetComponents()->size(); j++)
	//{
	//	if (m_entities.back()->GetComponents()->at(j)->Type() == "PC")
	//	{
	//		pcKey = j;
	//	}
	//	else if (m_entities.back()->GetComponents()->at(j)->Type() == "SC")
	//	{
	//		scKey = j;
	//	}
	//	if (scKey > 0 && pcKey > 0)
	//	{
	//		break;
	//	}
	//}
	//m_positionComponent.push_back(static_cast<PositionComponent>(m_entities.back()->GetComponents()->at(pcKey)));
	//m_spriteComponent.push_back(static_cast<SpriteComponent>(m_entities.back()->GetComponents()->at(scKey)));
}

void MovementSystem::UnloadComponent(int x)
{
	//m_positionComponent.erase(m_positionComponent.begin() + x);
	//m_spriteComponent.erase(m_spriteComponent.begin() + x);
	//m_positionComponent.shrink_to_fit();
	//m_spriteComponent.shrink_to_fit();
}

void MovementSystem::Update(float deltaTime)
{
	SDL_GetMouseState(&m_mouseX, &m_mouseY);

	// looks for if there is a position and movement component in the entity
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->Active())
		{
			int mcKey = -1;
			int pcKey = -1;
			int collisionKey = -1;

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
				else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "collision")
				{
					collisionKey = j;
				}
			}

			// makes sure it finds a position and movement component in the entity
			if (mcKey >= 0 && pcKey >= 0)
			{
				float* xPos = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getXRef();
				float* yPos = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getYRef();

				*xPos += static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getXVelocity() * deltaTime;
				*yPos += static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getYVelocity() * deltaTime;

				if (collisionKey >= 0)
				{
					static_cast<CollisionComponent*>(m_entities.at(i)->GetComponents()->at(collisionKey))->setPosition(*xPos, *yPos);
				}

				if (m_entities.at(i)->ID() == "Player")
				{
					if (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getLockedOrientation() == false) {
						static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setOrientation((atan2((float)m_mouseY - *yPos, (float)m_mouseX - *xPos)) * (180 / 3.142) + 90);
					}
				}
			}
		}
	}
}