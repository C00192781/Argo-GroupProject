#include "MovementSystem.h"

void MovementSystem::Update(float deltaTime)
{
	SDL_GetMouseState(&m_mouseX, &m_mouseY);

	// looks for if there is a position and movement component in the entity
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->Active())
		{
			PositionComponent* positionComponent = static_cast<PositionComponent*>(m_entities.at(i)->FindComponent("PC"));
			CollisionComponent* collisionComponent = static_cast<CollisionComponent*>(m_entities.at(i)->FindComponent("collision"));
			MovementComponent* movementComponent = static_cast<MovementComponent*>(m_entities.at(i)->FindComponent("movement"));

			positionComponent->setX(collisionComponent->getX());
			positionComponent->setY(collisionComponent->getY());
			collisionComponent->setPreviousPosition(positionComponent->getX(), positionComponent->getY());

			if (countedFrames[0] > 15 && m_entities.at(i)->ID() == "Player") //if all 15 roll frames have passed.
			{
				//cooldown on rolling
				countedFrames[0] = 0;
				cooldownFrames[0] = 60; //
				m_rollEnd = true;
				movementComponent->setLockedOrientation(false);
			}

			if (movementComponent != nullptr && positionComponent != nullptr && collisionComponent != nullptr)
			{
				if (m_entities.at(i)->ID() == "Player" && m_entities.at(i)->Control())
				{
					SpriteComponent* temp = static_cast<SpriteComponent*>(m_entities.at(i)->FindComponent("SC"));
					temp->Direction(0); //undo temporary roll animation

					if (movementComponent->getRolling() && cooldownFrames[0] < 1)
					{
						countedFrames[0]++;


						if (m_rollEnd)
						{
							collisionComponent->setPosition(collisionComponent->getX() + ((movementComponent->getXVelocity() * 4)* deltaTime),
								collisionComponent->getY() + ((movementComponent->getYVelocity() * 4)* deltaTime));

							m_lastXVel = (movementComponent->getXVelocity() * 4)* deltaTime;
							m_lastYVel = (movementComponent->getYVelocity() * 4)* deltaTime;

							if (m_lastXVel == 0 && m_lastYVel == 0) //default a roll orientation if no velo
							{
								m_lastXVel = 7; //future note: careful of clipping thru walls in this kinda scenario
								m_lastYVel = 7;
							}
							m_rollEnd = false;
						}
						else
						{
							collisionComponent->setPosition(collisionComponent->getX() + m_lastXVel, collisionComponent->getY() + m_lastYVel);
						}

						movementComponent->setLockedOrientation(true);

						if (countedFrames[0] > 15) //after 15f, roll ends. 
						{
							//end invincibility here.
							movementComponent->setRolling(false);
						}

						else if (countedFrames[0] < 15 && countedFrames[0] > 0)
						{
							auto temp = m_entities.at(i)->FindComponent("SC");
							static_cast<SpriteComponent*>(temp)->Direction(1); //temporary roll animation //play anim												   											   
						}
					}
					else
					{
						collisionComponent->setPosition(collisionComponent->getX() + (movementComponent->getXVelocity() * deltaTime),
							collisionComponent->getY() + (movementComponent->getYVelocity() * deltaTime));

						if (cooldownFrames[0] > 0)
						{
							cooldownFrames[0]--; //15frame cooldown on spamming roll.
						}

						if (cooldownFrames[0] > 5)
						{
							movementComponent->setRolling(false);
						}
					}

					if (movementComponent->getLockedOrientation() == false)
					{
						if (m_eventListener->controllerActivated == false)
						{
							movementComponent->setOrientation((atan2((float)m_mouseY - (m_windowHeight / 2), (float)m_mouseX - (m_windowWidth / 2))) * (180 / 3.142) + 90);
						}
						else
						{
							float cosA = m_eventListener->RightStick;
							movementComponent->setOrientation(cosA);
						}
					}

				}

				if (movementComponent->getLockedOrientation() == false)
				{
					collisionComponent->setPosition(collisionComponent->getX() + movementComponent->getXVelocity() * deltaTime,
						collisionComponent->getY() + movementComponent->getYVelocity() * deltaTime);
				}
			}
		}//end active

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
	//m_positionComponent.push_back(static_cast<PositionComponent*>(m_entities.back()->GetComponents()->at(pcKey)));
	//m_movementComponent.push_back(static_cast<MovementComponent*>(m_entities.back()->GetComponents()->at(movementKey)));
	//m_collisionComponent.push_back(static_cast<CollisionComponent*>(m_entities.back()->GetComponents()->at(collisionKey)));
}

void MovementSystem::UnloadComponent(int x)
{
	//m_positionComponent.erase(m_positionComponent.begin() + x);
	//m_movementComponent.erase(m_movementComponent.begin() + x);
	//m_collisionComponent.erase(m_collisionComponent.begin() + x);
	//m_positionComponent.shrink_to_fit();
	//m_movementComponent.shrink_to_fit();
	//m_collisionComponent.shrink_to_fit();
}