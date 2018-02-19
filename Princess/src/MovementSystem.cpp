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

			if (countedFrames > 30 && m_entities.at(i)->ID() == "Player") //if all 30 roll frames have passed.
			{
				//cooldown on rolling
				countedFrames = 0;
				cooldownFrames = 120; //

				SpriteComponent* temp = static_cast<SpriteComponent*>(m_entities.at(i)->FindComponent("SC"));
				temp->Direction(0); //undo temporary roll animation
				movementComponent->setLockedOrientation(false);
			}

			if (movementComponent != nullptr && positionComponent != nullptr && collisionComponent != nullptr)
			{
				if (m_entities.at(i)->ID() == "Player")
				{
					if (movementComponent->getRolling() && cooldownFrames < 1)
					{
						countedFrames++;

						if (!movementComponent->getLockedOrientation())
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
						}
						else
						{
							collisionComponent->setPosition(collisionComponent->getX() + m_lastXVel, collisionComponent->getY() + m_lastYVel);
						}

						movementComponent->setLockedOrientation(true);

						if (countedFrames > 30) //after 30f, roll ends. 
						{
							//end invincibility here.
							movementComponent->setRolling(false);
						}

						else if (countedFrames < 30 && countedFrames > 0)
						{
							auto temp = m_entities.at(i)->FindComponent("SC");
							static_cast<SpriteComponent*>(temp)->Direction(1); //temporary roll animation //play anim												   											   
						}
					}
					else
					{
						collisionComponent->setPosition(collisionComponent->getX() + (movementComponent->getXVelocity() * deltaTime),
							collisionComponent->getY() + (movementComponent->getYVelocity() * deltaTime));

						if (cooldownFrames > 0)
						{
							cooldownFrames--; //30frame cooldown on spamming roll.
						}

						if (cooldownFrames > 5)
						{
							movementComponent->setRolling(false);
						}
					}

					if (movementComponent->getLockedOrientation() == false)
					{
						movementComponent->setOrientation((atan2((float)m_mouseY - (m_windowHeight / 2), (float)m_mouseX - (m_windowWidth / 2))) * (180 / 3.142) + 90);
					}
				}
				else
				{
					collisionComponent->setPosition(collisionComponent->getX() + movementComponent->getXVelocity() * deltaTime,
													collisionComponent->getY() + movementComponent->getYVelocity() * deltaTime);	
				}
			}

			//			if (moveIndex != -1 && m_entities.at(i)->ID() == "Player" && posIndex != -1)
			//			{
			//				float* xPos = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(posIndex))->getXRef();
			//				float* yPos = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(posIndex))->getYRef();
			//
			//				if (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getRolling() && cooldownFrames < 1) //if roll isnt on cooldown and we wanna roll
			//				{
			//
			//					//assign roll invincibility here at some point.
			//					countedFrames++;
			//				//		std::cout << "timer: " << countedFrames << std::endl;
			//
			//					if (!static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getLockedOrientation())
			//					{
			//						*xPos += (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getXVelocity() * 4) * deltaTime; //rolls are fast.
			//						*yPos += (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getYVelocity() * 4) * deltaTime;
			//
			//						m_lastXVel = (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getXVelocity() * 4) * deltaTime; //lock roll to last given velocity
			//						m_lastYVel = (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getYVelocity() * 4) * deltaTime;
			//
			//						if (m_lastXVel == 0 && m_lastYVel == 0) //default a roll orientation if no velo
			//						{
			//							m_lastXVel = 7; //future note: careful of clipping thru walls in this kinda scenario
			//							m_lastYVel = 7;
			//						}
			//
			//					}
			//					else
			//					{
			//						*xPos += m_lastXVel; //locked roll rolls in given dir
			//						*yPos += m_lastYVel;
			//					}
			//
			//					static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->setLockedOrientation(true);
			//
			//					if (countedFrames > 30) //after 30f, roll ends. 
			//					{
			//						//end invincibility here.
			//						static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->setRolling(false);
			//					}
			//					
			//					else if (countedFrames < 30 && countedFrames > 0)
			//					{
			//
			//						auto temp = m_entities.at(i)->FindComponent("SC");
			//
			//						static_cast<SpriteComponent*>(temp)->Direction(1); //temporary roll animation
			//																		   //play anim
			//
			//																		   
			//					}
			//		
			//				}
			//
			//				else
			//				{
			//					*xPos += (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getXVelocity()) * deltaTime;
			//					*yPos += (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getYVelocity()) * deltaTime;
			//					if (cooldownFrames > 0)
			//					{
			//						cooldownFrames--; //30frame cooldown on spamming roll.
			//					}
			//
			//					if (cooldownFrames > 5)
			//					{
			//						static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->setRolling(false);
			//					}
			//
			//					//			std::cout << "on cd" << cooldownFrames << std::endl;
			//				}
			//
			//				if (m_entities.at(i)->ID() == "Player")
			//				{
			//					if (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getLockedOrientation() == false)
			//					{
			//						static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->setOrientation((atan2((float)m_mouseY - *yPos, (float)m_mouseX - *xPos)) * (180 / 3.142) + 90);
			//					}
			//
			//				}
			//
			//				static_cast<CollisionComponent*>(m_entities.at(i)->GetComponents()->at(collIndex))->setPosition(*xPos, *yPos);
			//
			//			}

//<<<<<<< HEAD
//			m_positionComponent.at(i)->setX(m_collisionComponent.at(i)->getX());
//			m_positionComponent.at(i)->setY(m_collisionComponent.at(i)->getY());
//			m_collisionComponent.at(i)->setPreviousPosition(m_collisionComponent.at(i)->getX(), m_collisionComponent.at(i)->getY());
//=======
//			int moveIndex = (m_entities.at(i)->FindComponentIndex("movement"));
//			int posIndex = (m_entities.at(i)->FindComponentIndex("PC"));
//			int collIndex = (m_entities.at(i)->FindComponentIndex("collision"));
//			float* xPos = m_positionComponent.at(i)->getXRef();
//			float* yPos = m_positionComponent.at(i)->getYRef();
//>>>>>>> master
//
//			m_collisionComponent.at(i)->setPosition(m_collisionComponent.at(i)->getX() + m_movementComponent.at(i)->getXVelocity() * deltaTime,
//													m_collisionComponent.at(i)->getY() + m_movementComponent.at(i)->getYVelocity() * deltaTime);		
//
//			if (countedFrames > 30 && m_entities.at(i)->ID() == "Player") //if all 30 roll frames have passed.
//			{
//				//cooldown on rolling
//				countedFrames = 0;
//				cooldownFrames = 120; //
//
//				auto temp = m_entities.at(i)->FindComponent("SC");
//
//				static_cast<SpriteComponent*>(temp)->Direction(0); //undo temporary roll animation
//
//																   //	std::cout << "cd " << std::endl;
//			//	int moveIndex = (m_entities.at(i)->FindComponentIndex("movement"));
//				static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->setLockedOrientation(false);
//
//			}
//
//			if (moveIndex != -1 && m_entities.at(i)->ID() == "Player" && posIndex != -1)
//			{
//				float* xPos = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(posIndex))->getXRef();
//				float* yPos = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(posIndex))->getYRef();
//
//				if (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getRolling() && cooldownFrames < 1) //if roll isnt on cooldown and we wanna roll
//				{
//
//					//assign roll invincibility here at some point.
//					countedFrames++;
//				//		std::cout << "timer: " << countedFrames << std::endl;
//
//					if (!static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getLockedOrientation())
//					{
//						*xPos += (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getXVelocity() * 4) * deltaTime; //rolls are fast.
//						*yPos += (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getYVelocity() * 4) * deltaTime;
//
//						m_lastXVel = (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getXVelocity() * 4) * deltaTime; //lock roll to last given velocity
//						m_lastYVel = (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getYVelocity() * 4) * deltaTime;
//
//						if (m_lastXVel == 0 && m_lastYVel == 0) //default a roll orientation if no velo
//						{
//							m_lastXVel = 7; //future note: careful of clipping thru walls in this kinda scenario
//							m_lastYVel = 7;
//						}
//
//					}
//					else
//					{
//						*xPos += m_lastXVel; //locked roll rolls in given dir
//						*yPos += m_lastYVel;
//					}
//
//					static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->setLockedOrientation(true);
//
//					if (countedFrames > 30) //after 30f, roll ends. 
//					{
//						//end invincibility here.
//						static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->setRolling(false);
//					}
//					
//					else if (countedFrames < 30 && countedFrames > 0)
//					{
//
//						auto temp = m_entities.at(i)->FindComponent("SC");
//
//						static_cast<SpriteComponent*>(temp)->Direction(1); //temporary roll animation
//																		   //play anim
//
//																		   
//					}
//		
//				}
//
//				else
//				{
//					*xPos += (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getXVelocity()) * deltaTime;
//					*yPos += (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getYVelocity()) * deltaTime;
//					if (cooldownFrames > 0)
//					{
//						cooldownFrames--; //30frame cooldown on spamming roll.
//					}
//
//					if (cooldownFrames > 5)
//					{
//						static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->setRolling(false);
//					}
//
//					//			std::cout << "on cd" << cooldownFrames << std::endl;
//				}
//
//				if (m_entities.at(i)->ID() == "Player")
//				{
//					if (static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->getLockedOrientation() == false)
//					{
//						static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(moveIndex))->setOrientation((atan2((float)m_mouseY - *yPos, (float)m_mouseX - *xPos)) * (180 / 3.142) + 90);
//					}
//
//				}
//
//				static_cast<CollisionComponent*>(m_entities.at(i)->GetComponents()->at(collIndex))->setPosition(*xPos, *yPos);
//
//			}
//
//			if (m_entities.at(i)->ID() == "Player")
//			{
//				if (m_movementComponent.at(i)->getLockedOrientation() == false)
//				{
//					m_movementComponent.at(i)->setOrientation((atan2((float)m_mouseY - (m_windowHeight / 2), (float)m_mouseX - (m_windowWidth / 2))) * (180 / 3.142) + 90);
//				}
//			}
//
//
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