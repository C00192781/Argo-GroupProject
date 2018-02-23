#include "ControlSystem.h"
#include <iostream>

void ControlSystem::Update()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		MovementComponent* movementComponent = static_cast<MovementComponent*>(m_entities.at(i)->FindComponent("movement"));
		WeaponComponent* weaponComponent = static_cast<WeaponComponent*>(m_entities.at(i)->FindComponent("weapon"));
		AttributesComponent* atrributeComponent = static_cast<AttributesComponent*>(m_entities.at(i)->FindComponent("attribute"));

		// looks for if there is are specific components in the entity
		if (movementComponent != nullptr && atrributeComponent != nullptr)
		{
			SDL_Point holder{ 0, 0 };

			movementComponent->setMoving(false);
			if (m_eventListener->controllerActivated == false)
			{
				if (m_eventListener->roll)
				{
					//do roll stuff;
					movementComponent->setRolling(true);
				}
				if (m_eventListener->W)
				{
					holder.y = -atrributeComponent->MovementSpeed();

					movementComponent->setMoving(true);
					totalPlayerMovement += 1;
				}
				if (m_eventListener->A)
				{
					holder.x = -atrributeComponent->MovementSpeed();
					movementComponent->setMoving(true);
					totalPlayerMovement += 1;
				}
				if (m_eventListener->S)
				{
					holder.y = atrributeComponent->MovementSpeed();
					movementComponent->setMoving(true);
					totalPlayerMovement += 1;
				}
				if (m_eventListener->D)
				{
					holder.x = atrributeComponent->MovementSpeed();
					movementComponent->setMoving(true);
					totalPlayerMovement += 1;
				}
				if (!m_eventListener->roll) //course changable if not rolling
				{
					//	cout << movementComponent->getXVelocity() << endl;

					movementComponent->setVelocity(holder.x, holder.y);
				}
			}
			else
			{
				float tempX;
				float tempY;
				float x = m_eventListener->LeftStickX;
				float y = m_eventListener->LeftStickY;

				float leftJoystickAngle = atan2(y, x) + 3.14159265359 / 180 * 90;

				tempX = sin(leftJoystickAngle);
				tempY = -cos(leftJoystickAngle);

				std::cout << tempX << std::endl;

				holder.x = (atrributeComponent->MovementSpeed() * tempX) * 1.25;
				if (x > -8000 && x < 8000)
				{
					holder.x = 0;
				}

				holder.y = (atrributeComponent->MovementSpeed() * tempY) * 1.25;
				if (y > -8000 && y < 8000)
				{
					holder.y = 0;
				}

				if (m_eventListener->BButton)
				{
					//do roll stuff;
					movementComponent->setRolling(true);
				}
				if (m_eventListener->UpButton)
				{
					holder.y = -atrributeComponent->MovementSpeed();

					movementComponent->setMoving(true);
					totalPlayerMovement += 1;
				}
				if (m_eventListener->LeftButton)
				{
					holder.x = -atrributeComponent->MovementSpeed();
					movementComponent->setMoving(true);
					totalPlayerMovement += 1;
				}
				if (m_eventListener->DownButton)
				{
					holder.y = atrributeComponent->MovementSpeed();
					movementComponent->setMoving(true);
					totalPlayerMovement += 1;
				}
				if (m_eventListener->RightButton)
				{
					holder.x = atrributeComponent->MovementSpeed();
					movementComponent->setMoving(true);
					totalPlayerMovement += 1;
				}
				if (!m_eventListener->BButton)
				{
					movementComponent->setVelocity(holder.x, holder.y);
				}
			}
		}

		if (movementComponent != nullptr && weaponComponent != nullptr)
		{
			if (!movementComponent->getRolling())
			{
				if (m_eventListener->LeftClick || m_eventListener->RightTrigger > 8000)
				{
					if (weaponComponent->getAllowAttack() == true)
					{
						weaponComponent->setAttacking(true);
						movementComponent->setLockedOrientation(true);
						weaponComponent->setAllowAttack(false);
					}
				}
			}
		}

	}
}
