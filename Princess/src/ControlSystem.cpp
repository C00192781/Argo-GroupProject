#include "ControlSystem.h"
#include <iostream>

void ControlSystem::Update()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		int mcKey = -1;
		int pjKey = -1;
		int pcKey = -1;
		int wcKey = -1;
		int attributeKey = -1;

		// looks for if there is are specific components in the entity
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
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "weapon")
			{
				wcKey = j;
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "attribute")
			{
				attributeKey = j;
			}
		}

		if (mcKey >= 0)
		{
			SDL_Point holder{ 0, 0 };
			int speed = static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(attributeKey))->MovementSpeed();

			if (m_eventListener->W)
			{
				holder.y = -speed;
				totalPlayerMovement += 1;
			}
			if (m_eventListener->A)
			{
				holder.x = -speed;
				totalPlayerMovement += 1;
			}
			if (m_eventListener->S)
			{
				holder.y = speed;
				totalPlayerMovement += 1;
			}
			if (m_eventListener->D)
			{
				holder.x = speed;
				totalPlayerMovement += 1;
			}

			static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setVelocity(holder.x, holder.y);
		}

		if (wcKey >= 0)
		{
			if (m_eventListener->LeftClick)
			{
				if (static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getAllowAttack() == true)
				{
					static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->setAttacking(true);
					static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setLockedOrientation(true);
					static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->setAllowAttack(false);
				}
			}
		}
	}
}

