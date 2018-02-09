#include "AttackSystem.h"

AttackSystem::AttackSystem(std::vector<Entity*>* projectiles)
{
	m_projectiles = projectiles;
}

void AttackSystem::Update(float deltaTime)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		int wcKey = -1;
		int pcKey = -1;
		int mcKey = -1;

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
						}
						else
						{
							temp = static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getMaxTimeForAttack();
							static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->setAttacking(false);
							static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setLockedOrientation(false);
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
					// if the entity is already attacking
					if (static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getAttacking() == true)
					{
						for (int j = 0; j < m_projectiles->size(); j++)
						{
							if (m_projectiles->at(j)->Active() == false)
							{
								int projectileMCKey = -1;
								int projectilePJKey = -1;
								int projectilePCKey = -1;

								for (int k = 0; k < m_projectiles->at(j)->GetComponents()->size(); k++)
								{
									if (m_projectiles->at(j)->GetComponents()->at(k)->Type() == "movement")
									{
										projectileMCKey = k;
									}
									else if (m_projectiles->at(j)->GetComponents()->at(k)->Type() == "PJ")
									{
										projectilePJKey = k;
									}
									else if (m_projectiles->at(j)->GetComponents()->at(k)->Type() == "PC")
									{
										projectilePCKey = k;
									}
								}
								m_projectiles->at(j)->Active(true);
								static_cast<ProjectileComponent*>(m_projectiles->at(j)->GetComponents()->at(projectilePJKey))->setShooterType(m_entities.at(i)->ID());
								float temp = static_cast<ProjectileComponent*>(m_projectiles->at(j)->GetComponents()->at(projectilePJKey))->getBaseSpeed() * static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getAttackSpeed() * deltaTime;
								static_cast<ProjectileComponent*>(m_projectiles->at(j)->GetComponents()->at(projectilePJKey))->setTimeToLive(static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->getRange() / temp);
								static_cast<PositionComponent*>(m_projectiles->at(j)->GetComponents()->at(projectilePCKey))->setPosition(static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getX(), static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getY());

								static_cast<MovementComponent*>(m_projectiles->at(j)->GetComponents()->at(projectileMCKey))->setXVelocity((sin(static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getOrientation()* (3.142 / 180)) * temp) * 1000);
								static_cast<MovementComponent*>(m_projectiles->at(j)->GetComponents()->at(projectileMCKey))->setYVelocity((-cos(static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->getOrientation() * (3.142 / 180)) * temp) * 1000);

								break;
							}
						}
						static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->setAttacking(false);
						static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(wcKey))->setAllowAttack(true);
						static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setLockedOrientation(false);
					}
				}
				// if the entity has a magic weapon
				else
				{

				}
			}
		}
	}
}