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
				movementComponent->setVelocity(holder.x, holder.y);
			}
		}

		if (movementComponent != nullptr && weaponComponent != nullptr)
		{
			if (!movementComponent->getRolling())
			{
				if (m_eventListener->LeftClick)
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
