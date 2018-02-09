#include "ControlSystem.h"
#include <iostream>

void ControlSystem::Update()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		int mcKey = -1;
		int pjKey = -1;
		int playerKey = -1;
		int acKey = -1;

		// looks for if there is a movement component in the entity
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "movement")
				{
					mcKey = j;
				}
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PJ")
				{
					pjKey = j;
				}
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC" && m_entities.at(i)->ID() == "Player")
				{
					playerKey = j;
					if (m_entities.at(i)->GetComponents()->at(j)->Type() == "AC")
					{
						acKey = j;
					}
				}
			}
			if (playerKey >= 0)
			{
				playerPos = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(playerKey))->getPosition();
			}
			// makes sure it finds a movement component in the entity
			if (mcKey >= 0 && acKey >=0)
			{
				Vector2f holder{ 0, 0 };
				int speed = static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->MovementSpeed();
				if (m_eventListener->controllerActivated == false)
				{
					if (m_eventListener->W)
					{
						holder.y = -speed + 1;
					}
					if (m_eventListener->A)
					{
						holder.x = -speed + 1;
					}
					if (m_eventListener->S)
					{
						holder.y = speed - 1;
					}
					if (m_eventListener->D)
					{
						holder.x = speed - 1;
					}
				}
				else
				{
					float tempX;
					float tempY;
					float x = m_eventListener->LeftStickX;
					float y = m_eventListener->LeftStickY;

					float rightJoystickAngle = atan2(y, x) + 3.14159265359 / 180 * 90;

					tempX = sin(rightJoystickAngle);
					tempY = -cos(rightJoystickAngle);

					holder.x = speed * tempX;
					if (x > -8000 && x < 8000)
					{
						holder.x = 0;
					}

					holder.y = speed * tempY;
					if (y > -8000 && y < 8000)
					{
						holder.y = 0;
					}

					if (m_eventListener->UpButton)
					{
						holder.y = -speed + 1;
					}
					if (m_eventListener->LeftButton)
					{
						holder.x = -speed + 1;
					}
					if (m_eventListener->DownButton)
					{
						holder.y = speed - 1;
					}
					if (m_eventListener->RightButton)
					{
						holder.x = speed - 1;
					}
				}

				static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setXVelocity(holder.x);
				static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setYVelocity(holder.y);
			}
		}
		if (m_projectiles != nullptr)
		{
			for (int i = 0; i < m_projectiles->size(); i++)
			{
				int mcKey = -1;
				int pjKey = -1;
				int pcKey = -1;

				// looks for if there is a movement component in the entity
				for (int j = 0; j < m_projectiles->at(i)->GetComponents()->size(); j++)
				{
					for (int j = 0; j < m_projectiles->at(i)->GetComponents()->size(); j++)
					{
						if (m_projectiles->at(i)->GetComponents()->at(j)->Type() == "movement")
						{
							mcKey = j;
						}
						if (m_projectiles->at(i)->GetComponents()->at(j)->Type() == "PJ")
						{
							pjKey = j;
						}
						if (m_projectiles->at(i)->GetComponents()->at(j)->Type() == "PC")
						{
							pcKey = j;
						}
					}
				}
				if (m_eventListener->controllerActivated == false)
				{
					if (m_eventListener->LeftClick == true)
					{
						lastTickTime = tickTime;
						shoot = true;
					}
					if (m_eventListener->LeftClick == false)
					{
						float cosA;
						SDL_GetMouseState(&x, &y);
						cosA = atan2(y - playerPos.y, x - playerPos.x) + 3.14159265359 / 180 * 90;
		
						if (pjKey >= 0 && pcKey >= 0)
						{
							tickTime = SDL_GetTicks();

							uint32_t difference;
							difference = tickTime - lastTickTime;

							float differenceInSeconds;
							differenceInSeconds = (float)difference * 0.001f;

							if (difference > 50 && shoot == true)
							{
								index++;
								shoot = false;
								if (index >= m_projectiles->size())
								{
									index = 0;
								}
								if (static_cast<ProjectileComponent*>(m_projectiles->at(index)->GetComponents()->at(pjKey))->getType() == "Player")
								{
									static_cast<ProjectileComponent*>(m_projectiles->at(index)->GetComponents()->at(pjKey))->setAliveStatus(true);
									static_cast<ProjectileComponent*>(m_projectiles->at(index)->GetComponents()->at(pjKey))->setButtonPressTime(differenceInSeconds);
									static_cast<ProjectileComponent*>(m_projectiles->at(index)->GetComponents()->at(pjKey))->setOrientation(cosA);
									static_cast<PositionComponent*>(m_projectiles->at(index)->GetComponents()->at(pcKey))->setPosition(playerPos);
								
								}
							}
						}
					}
				}
				else if (m_eventListener->controllerActivated == true)
				{
					if (m_eventListener->RightTrigger > 8000)
					{
						lastTickTime = tickTime;
						shoot = true;
					}
					if (m_eventListener->RightTrigger <= 8000)
					{
						//std::cout << m_eventListener->controllerActivated << std::endl;
						float cosA;
						cosA = m_eventListener->RightStick;
						//std::cout << cosA << std::endl;
						
						if (pjKey >= 0 && pcKey >= 0)
						{
							tickTime = SDL_GetTicks();

							uint32_t difference;
							difference = tickTime - lastTickTime;

							float differenceInSeconds;
							differenceInSeconds = (float)difference * 0.001f;

							if (difference > 50 && shoot == true)
							{
								index++;
								shoot = false;
								if (index >= m_projectiles->size())
								{
									index = 0;
								}
								if (static_cast<ProjectileComponent*>(m_projectiles->at(index)->GetComponents()->at(pjKey))->getType() == "Player")
								{
									static_cast<ProjectileComponent*>(m_projectiles->at(index)->GetComponents()->at(pjKey))->setAliveStatus(true);
									static_cast<ProjectileComponent*>(m_projectiles->at(index)->GetComponents()->at(pjKey))->setButtonPressTime(differenceInSeconds);
									static_cast<ProjectileComponent*>(m_projectiles->at(index)->GetComponents()->at(pjKey))->setOrientation(cosA);
									static_cast<PositionComponent*>(m_projectiles->at(index)->GetComponents()->at(pcKey))->setPosition(playerPos);
									//static_cast<ProjectileComponent*>(m_projectiles->at(index)->GetComponents()->at(pjKey))->setMaxSpeed(15.0f);
								}
							}
						}
					}
				}
			}
		}
	}
}

//			//	mc->setAliveStatus(false);
//				//int velocityX = mc->getSpeed();
//				//std::cout << m_projectiles->at(i)->ID() << " " << velocityX << std::endl;
//			//MovementComponent move;
//			//m_projectiles->at(6)->AddComponent(new MovementComponent());
//			//m_projectiles->at(6)->RemoveComponent()
//