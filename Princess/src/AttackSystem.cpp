#include "AttackSystem.h"

AttackSystem::AttackSystem(std::vector<Entity*>* projectiles)
{
	m_projectiles = projectiles;
}

void AttackSystem::LoadComponent()
{
	//int pcKey = -1;
	//int scKey = -1;
	//for (int j = 0; j < m_entities.back()->GetComponents()->size(); j++)
	//{
	//	if (m_entities.back()->GetComponents()->at(j)->Type() == "PC")
	//	{
	//		pcKey = j;
	//	}
	//	else if (m_entities.back()->GetComponents()->at(j)->Type() == "SC")
	//	{
	//		scKey = j;
	//	}
	//	if (scKey > 0 && pcKey > 0)
	//	{
	//		break;
	//	}
	//}
	//m_positionComponent.push_back(static_cast<PositionComponent>(m_entities.back()->GetComponents()->at(pcKey)));
	//m_spriteComponent.push_back(static_cast<SpriteComponent>(m_entities.back()->GetComponents()->at(scKey)));
}

void AttackSystem::UnloadComponent(int x)
{
	//m_positionComponent.erase(m_positionComponent.begin() + x);
	//m_spriteComponent.erase(m_spriteComponent.begin() + x);
	//m_positionComponent.shrink_to_fit();
	//m_spriteComponent.shrink_to_fit();
}

void AttackSystem::Update(float deltaTime)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->Active())
		{
			PositionComponent* positionComponent = nullptr;
			MovementComponent* movementComponent = nullptr;
			ProjectileComponent* projectileComponent = nullptr;
			WeaponComponent* weaponComponent = nullptr;


			// looks for if there is are specific components in the entity
			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC")
				{
					positionComponent = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(j));
				}
				else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "movement")
				{
					movementComponent = static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(j));
				}
				else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "weapon")
				{
					weaponComponent = static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(j));
				}
				else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PJ")
				{
					projectileComponent = static_cast<ProjectileComponent*>(m_entities.at(i)->GetComponents()->at(j));
				}
			}

			if (positionComponent != nullptr && movementComponent != nullptr && weaponComponent != nullptr)
			{
				// if the entity is not allowed to attack
				if (weaponComponent->getAllowAttack() == false)
				{
					// if the weapon the entity uses is a melee weapon
					if (weaponComponent->getWeaponType() == WeaponType::MELEE)
					{
						// if the entity is already attacking
						if (weaponComponent->getAttacking() == true)
						{
							int count = 0;

							for (int j = 0; j < m_projectiles->size(); j++)
							{
								if (count < 3)
								{
									if (m_projectiles->at(j)->Active() == false)
									{
										ProjectileComponent* newProjectileComponent = nullptr;
										PositionComponent* projectilePositionComponent = nullptr;
										MovementComponent* projectileMovementComponent = nullptr;

										for (int k = 0; k < m_projectiles->at(j)->GetComponents()->size(); k++)
										{
											if (m_projectiles->at(j)->GetComponents()->at(k)->Type() == "movement")
											{
												projectileMovementComponent = static_cast<MovementComponent*>(m_projectiles->at(j)->GetComponents()->at(k));
											}
											else if (m_projectiles->at(j)->GetComponents()->at(k)->Type() == "PJ")
											{
												newProjectileComponent = static_cast<ProjectileComponent*>(m_projectiles->at(j)->GetComponents()->at(k));
											}
											else if (m_projectiles->at(j)->GetComponents()->at(k)->Type() == "PC")
											{
												projectilePositionComponent = static_cast<PositionComponent*>(m_projectiles->at(j)->GetComponents()->at(k));
											}
										}
										m_projectiles->at(j)->Active(true);
										newProjectileComponent->setShooterType(m_entities.at(i)->ID());
										newProjectileComponent->setTimeToLive(weaponComponent->getRange() * deltaTime);
										projectilePositionComponent->setPosition(positionComponent->getX(), positionComponent->getY());

										if (count == 0)
										{
											projectileMovementComponent->setXVelocity((sin((movementComponent->getOrientation() - 20) * (3.142 / 180)) * newProjectileComponent->getBaseSpeed()));
											projectileMovementComponent->setYVelocity((-cos((movementComponent->getOrientation() - 20) * (3.142 / 180)) * newProjectileComponent->getBaseSpeed()));
										}
										else if (count == 1)
										{
											projectileMovementComponent->setXVelocity((sin((movementComponent->getOrientation() + 20) * (3.142 / 180)) * newProjectileComponent->getBaseSpeed()));
											projectileMovementComponent->setYVelocity((-cos((movementComponent->getOrientation() + 20) * (3.142 / 180)) * newProjectileComponent->getBaseSpeed()));
										}
										else
										{
											projectileMovementComponent->setXVelocity((sin(movementComponent->getOrientation() * (3.142 / 180)) * newProjectileComponent->getBaseSpeed()));
											projectileMovementComponent->setYVelocity((-cos(movementComponent->getOrientation()  * (3.142 / 180)) * newProjectileComponent->getBaseSpeed()));
										}

										weaponComponent->setAttacking(false);
										movementComponent->setLockedOrientation(false);

										count++;
									}
								}
								else
								{
									break;
								}
							}
						}
						else
						{
							float temp = weaponComponent->getTimeToAllowAttack();

							// checks for if allowed to attack
							if (temp > 0)
							{
								temp -= deltaTime;
							}
							else
							{
								temp = weaponComponent->getMaxTimeToAllowAttack();
								weaponComponent->setAllowAttack(true);
							}

							weaponComponent->setTimeToAllowAttack(temp);
						}
						//{
						//	float temp = weaponComponent->getTimeForAttack();
						//
						//	// checks for if still attacking
						//	if (temp > 0)
						//	{
						//		temp -= deltaTime;
						//	}
						//	else
						//	{
						//		temp = weaponComponent->getMaxTimeForAttack();
						//		weaponComponent->setAttacking(false);
						//		movementComponent->setLockedOrientation(false);
						//	}
						//
						//	weaponComponent->setTimeForAttack(temp);
						//}
						//
						//float temp = weaponComponent->getTimeToAllowAttack();
						//
						//// checks for if allowed to attack
						//if (temp > 0)
						//{
						//	temp -= deltaTime;
						//}
						//else
						//{
						//	temp = weaponComponent->getMaxTimeToAllowAttack();
						//	weaponComponent->setAllowAttack(true);
						//}
						//
						//weaponComponent->setTimeToAllowAttack(temp);
					}
					// if the entity has a ranged weapon
					else if (weaponComponent->getWeaponType() == WeaponType::RANGE)
					{
						// if the entity is already attacking
						if (weaponComponent->getAttacking() == true)
						{
							for (int j = 0; j < m_projectiles->size(); j++)
							{
								if (m_projectiles->at(j)->Active() == false)
								{
									ProjectileComponent* newProjectileComponent = nullptr;
									PositionComponent* projectilePositionComponent = nullptr;
									MovementComponent* projectileMovementComponent = nullptr;
						
									for (int k = 0; k < m_projectiles->at(j)->GetComponents()->size(); k++)
									{
										if (m_projectiles->at(j)->GetComponents()->at(k)->Type() == "movement")
										{
											projectileMovementComponent = static_cast<MovementComponent*>(m_projectiles->at(j)->GetComponents()->at(k));
										}
										else if (m_projectiles->at(j)->GetComponents()->at(k)->Type() == "PJ")
										{
											newProjectileComponent = static_cast<ProjectileComponent*>(m_projectiles->at(j)->GetComponents()->at(k));
										}
										else if (m_projectiles->at(j)->GetComponents()->at(k)->Type() == "PC")
										{
											projectilePositionComponent = static_cast<PositionComponent*>(m_projectiles->at(j)->GetComponents()->at(k));
										}
									}
									m_projectiles->at(j)->Active(true);
									newProjectileComponent->setShooterType(m_entities.at(i)->ID());
									//float temp = newProjectileComponent->getBaseSpeed() * weaponComponent->getAttackSpeed() * deltaTime;
									newProjectileComponent->setTimeToLive(weaponComponent->getRange() * deltaTime);
									projectilePositionComponent->setPosition(positionComponent->getX(), positionComponent->getY());
						
									projectileMovementComponent->setXVelocity((sin(movementComponent->getOrientation()* (3.142 / 180)) * newProjectileComponent->getBaseSpeed()));
									projectileMovementComponent->setYVelocity((-cos(movementComponent->getOrientation() * (3.142 / 180)) * newProjectileComponent->getBaseSpeed()));

									//projectileMovementComponent->setXVelocity((sin(movementComponent->getOrientation()* (3.142 / 180)) * (temp / (deltaTime / 4))));
									//projectileMovementComponent->setYVelocity((-cos(movementComponent->getOrientation() * (3.142 / 180)) * (temp / (deltaTime / 4))));

									weaponComponent->setAttacking(false);
									movementComponent->setLockedOrientation(false);
						
									break;
								}
							}
						}
						else
						{
							float temp = weaponComponent->getTimeToAllowAttack();

							// checks for if allowed to attack
							if (temp > 0)
							{
								temp -= deltaTime;
							}
							else
							{
								temp = weaponComponent->getMaxTimeToAllowAttack();
								weaponComponent->setAllowAttack(true);
							}

							weaponComponent->setTimeToAllowAttack(temp);
						}
					}
					// if the entity has a magic weapon
					else
					{
						// if the entity is already attacking
						if (weaponComponent->getAttacking() == true)
						{
							for (int j = 0; j < m_projectiles->size(); j++)
							{
								if (m_projectiles->at(j)->Active() == false)
								{
									ProjectileComponent* newProjectileComponent = nullptr;
									PositionComponent* projectilePositionComponent = nullptr;
									MovementComponent* projectileMovementComponent = nullptr;

									for (int k = 0; k < m_projectiles->at(j)->GetComponents()->size(); k++)
									{
										if (m_projectiles->at(j)->GetComponents()->at(k)->Type() == "movement")
										{
											projectileMovementComponent = static_cast<MovementComponent*>(m_projectiles->at(j)->GetComponents()->at(k));
										}
										else if (m_projectiles->at(j)->GetComponents()->at(k)->Type() == "PJ")
										{
											newProjectileComponent = static_cast<ProjectileComponent*>(m_projectiles->at(j)->GetComponents()->at(k));
										}
										else if (m_projectiles->at(j)->GetComponents()->at(k)->Type() == "PC")
										{
											projectilePositionComponent = static_cast<PositionComponent*>(m_projectiles->at(j)->GetComponents()->at(k));
										}
									}
									m_projectiles->at(j)->Active(true);
									newProjectileComponent->setShooterType(m_entities.at(i)->ID());
									newProjectileComponent->setTimeToLive(weaponComponent->getRange() * deltaTime);
									projectilePositionComponent->setPosition(positionComponent->getX(), positionComponent->getY());

									projectileMovementComponent->setXVelocity((sin((movementComponent->getOrientation() + weaponComponent->getStaffOffset())* (3.142 / 180)) * newProjectileComponent->getBaseSpeed()));
									projectileMovementComponent->setYVelocity((-cos((movementComponent->getOrientation() + weaponComponent->getStaffOffset()) * (3.142 / 180)) * newProjectileComponent->getBaseSpeed()));

									weaponComponent->setAttacking(false);
									movementComponent->setLockedOrientation(false);

									setStaffOffset(weaponComponent);

									break;
								}
							}
						}
						else
						{
							float temp = weaponComponent->getTimeToAllowAttack();

							// checks for if allowed to attack
							if (temp > 0)
							{
								temp -= deltaTime;
							}
							else
							{
								temp = weaponComponent->getMaxTimeToAllowAttack();
								weaponComponent->setAllowAttack(true);
							}

							weaponComponent->setTimeToAllowAttack(temp);
						}
					}
				}
			}
			if (projectileComponent != nullptr)
			{
				if (projectileComponent->getTimeToLive() > 0)
				{
					projectileComponent->setTimeToLive(projectileComponent->getTimeToLive() - deltaTime);
				}
				else
				{
					m_entities.at(i)->Active(false);
				}
			}
		}
	}
}

void AttackSystem::setStaffOffset(WeaponComponent* weapon)
{
	if (weapon->getStaffOffset() == -(weapon->getOffsetVariance() * 2))
	{
		weapon->setPreviousStaffOffset(weapon->getStaffOffset());
		weapon->setStaffOffset(-weapon->getOffsetVariance());
	}
	else if (weapon->getStaffOffset() == -weapon->getOffsetVariance() && weapon->getPreviousStaffOffset() == -(weapon->getOffsetVariance() * 2))
	{
		weapon->setPreviousStaffOffset(weapon->getStaffOffset());
		weapon->setStaffOffset(0);
	}
	else if (weapon->getStaffOffset() == -weapon->getOffsetVariance() && weapon->getPreviousStaffOffset() == 0)
	{
		weapon->setPreviousStaffOffset(weapon->getStaffOffset());
		weapon->setStaffOffset(-(weapon->getOffsetVariance() * 2));
	}
	else if (weapon->getStaffOffset() == 0 && weapon->getPreviousStaffOffset() == -weapon->getOffsetVariance())
	{
		weapon->setPreviousStaffOffset(weapon->getStaffOffset());
		weapon->setStaffOffset(weapon->getOffsetVariance());
	}
	else if (weapon->getStaffOffset() == 0 && weapon->getPreviousStaffOffset() == weapon->getOffsetVariance())
	{
		weapon->setPreviousStaffOffset(weapon->getStaffOffset());
		weapon->setStaffOffset(-weapon->getOffsetVariance());
	}
	else if (weapon->getStaffOffset() == weapon->getOffsetVariance() && weapon->getPreviousStaffOffset() == (weapon->getOffsetVariance() * 2))
	{
		weapon->setPreviousStaffOffset(weapon->getStaffOffset());
		weapon->setStaffOffset(0);
	}
	else if (weapon->getStaffOffset() == weapon->getOffsetVariance() && weapon->getPreviousStaffOffset() == 0)
	{
		weapon->setPreviousStaffOffset(weapon->getStaffOffset());
		weapon->setStaffOffset((weapon->getOffsetVariance() * 2));
	}
	else
	{
		weapon->setPreviousStaffOffset(weapon->getStaffOffset());
		weapon->setStaffOffset(weapon->getOffsetVariance());
	}
}