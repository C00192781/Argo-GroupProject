#include "AttackSystem.h"

void AttackSystem::Update()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		int wcKey = -1;
		int pcKey = -1;
		int pjKey = -1;
		int mcKey = -1;

		//std::string check = "Projectile";
		//
		//std::string playerCheck = "Player";

		// looks for if there is are specific components in the entity
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			//if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC" && m_entities.at(i)->ID() == check)
			//{
			//	pcKey = j;
			//}
			//else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PJ" && m_entities.at(i)->ID() == check)
			//{
			//	pjKey = j;
			//}
			//else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "movement" && m_entities.at(i)->ID() == check)
			//{
			//	mcKey = j;
			//}

			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC")
			{
				pcKey = j;
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PJ")
			{
				pjKey = j;
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "movement")
			{
				mcKey = j;
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "weapon")
			{
				wcKey = j;
			}
		}

		//if (pcKey >= 0 && pjKey >= 0 && mcKey >= 0 && wcKey >= 0)
		if (pcKey >= 0 && mcKey >= 0 && wcKey >= 0)
		{
			// if the entity is not allowed to attack
			if (static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getAllowAttack() == false)
			{
				// if the weapon the entity uses is a melee weapon
				if (static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getWeaponType() == WeaponType::MELEE)
				{
					// if the entity is already attacking
					if (static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getAttacking() == true)
					{
						float temp = static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getTimeForAttack();

						// checks for if still attacking
						if (temp > 0)
						{
							temp -= 0.01;
							//temp--;
						}
						else
						{
							temp = static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getMaxTimeForAttack();
							static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->setAttacking(false);
							static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setLockedOrientation(true);
						}

						static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->setTimeForAttack(temp);
					}

					float temp = static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getTimeToAllowAttack();

					// checks for if allowed to attack
					if (temp > 0)
					{
						temp -= 0.01;
						//temp--;
					}
					else
					{
						temp = static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getMaxTimeToAllowAttack();
						static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->setAllowAttack(true);
					}

					static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->setTimeToAllowAttack(temp);
				}
				// if the entity has a ranged weapon
				else if (static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getWeaponType() == WeaponType::RANGE)
				{

				}
				// if the entity has a magic weapon
				else
				{

				}
			}
		}
	}
}