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

			if (countedFrames > 30 && m_entities.at(i)->ID() == "Player") //if all 30 roll frames have passed.
			{
				//assign roll invincibility here at some point.
				countedFrames = 0;
				cooldownFrames = 30;
				static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setLockedOrientation(false);
			}

			// makes sure it finds a position and movement component in the entity
			if (mcKey >= 0 && pcKey >= 0)
			{
				float* xPos = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getXRef();
				float* yPos = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getYRef();

				if (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getRolling() && m_entities.at(i)->ID() == "Player" && cooldownFrames < 1) //if roll isnt on cooldown and we wanna roll
				{
					
					countedFrames++;
				//	std::cout << "timer: " << countedFrames << std::endl;
					
					if (!static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getLockedOrientation())
					{
						*xPos += (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getXVelocity() * 4) * deltaTime; //rolls are fast.
						*yPos += (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getYVelocity() * 4) * deltaTime;

						m_lastXVel = (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getXVelocity() * 4) * deltaTime; //lock roll to last given velocity
						m_lastYVel = (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getYVelocity() * 4) * deltaTime;

						if (m_lastXVel == 0 && m_lastYVel == 0) //default a roll orientation if no velo
						{
							m_lastXVel = 7; //future note: careful of clipping thru walls in this kinda scenario
							m_lastYVel = 7;
						}

					}
					else
					{
						*xPos += m_lastXVel; //locked roll rolls in given dir
						*yPos += m_lastYVel;
					}
					static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setLockedOrientation(true);

					if (countedFrames > 30) //after 30f, roll ends. 
					{
						//end invincibility here.
						static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setRolling(false);
					}

				}
				else
				{
					*xPos += (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getXVelocity()) * deltaTime;
					*yPos += (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getYVelocity()) * deltaTime;
					cooldownFrames--; //30frame cooldown on spamming roll.
				}

				if (collisionKey >= 0)
				{
					static_cast<CollisionComponent*>(m_entities.at(i)->GetComponents()->at(collisionKey))->setPosition(*xPos, *yPos);
				}

				if (m_entities.at(i)->ID() == "Player")
				{
					if (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getLockedOrientation() == false)
					{
						static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setOrientation((atan2((float)m_mouseY - *yPos, (float)m_mouseX - *xPos)) * (180 / 3.142) + 90);
					}

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