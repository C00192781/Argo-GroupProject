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

		if (pcKey >= 0 && pjKey >= 0 && mcKey >= 0 && wcKey >= 0)
		{
			if (static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getWeaponType() == WeaponType::MELEE)
			{
				if (static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getAttacking() == true)
				{
					float temp = static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getTimeForAttack();

					if (temp > 0)
					{
						temp--;
					}
					else
					{
						temp = static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getMaxTimeForAttack();
						static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->setAttacking(false);
					}
					static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->setTimeForAttack(temp);
				}
			}
			else if (static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getWeaponType() == WeaponType::RANGE)
			{

			}
			else
			{

			}
		}
	}
}