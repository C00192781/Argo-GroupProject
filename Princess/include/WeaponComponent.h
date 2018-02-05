#pragma once

#include "Component.h"
#include "WeaponType.h"

class WeaponComponent : public Component
{
public:
	WeaponComponent() {}

	WeaponComponent(WeaponType weaponType)
	{
		m_type = "weapon";

		m_weaponType = weaponType;

		if (m_weaponType == WeaponType::MELEE)
		{
			m_range = 10 + (rand() % 5);
			m_damage = 1 + (rand() % 9);
			setAttackSpeed(0.5 + ((float)(rand() % 250) / 100));
		}
		else if (m_weaponType == WeaponType::RANGE)
		{
			m_range = 50 + (rand() % 25);
			m_damage = 1 + (rand() % 9);
			setAttackSpeed(0.5 + ((float)(rand() % 250) / 100));
		}
		else
		{
			m_range = 40 + (rand() % 20);
			m_damage = 1 + (rand() % 9);
			setAttackSpeed(0.5 + ((float)(rand() % 250) / 100));
		}

		m_allowAttack = true;
		m_attacking = false;
	}

	void setRange(int range) { m_range = range; };
	void setDamage(int damage) { m_damage = damage; };
	void setAttackSpeed(float attackSpeed)
	{ 
		m_attackSpeed = attackSpeed;
		m_maxTimeToAllowAttack = 1 / attackSpeed;
		//m_maxTimeToAllowAttack = (1 / attackSpeed) * 1000; // TBD depends on deltatime
		m_timeToAllowAttack = m_maxTimeToAllowAttack;
		m_maxTimeForAttack = (1 / attackSpeed) / 2;
		//m_maxTimeForAttack = ((1 / attackSpeed) / 2) * 1000; // TBD depends on deltatime
		m_timeForAttack = m_maxTimeForAttack;
	};

	void setWeaponType(WeaponType type) { m_weaponType = type; };
	void setAllowAttack(bool allowAttack) { m_allowAttack = allowAttack; };
	void setTimeToAllowAttack(float time) {  m_timeToAllowAttack = time; };
	void setAttacking(bool attacking) { m_attacking = attacking; };
	void setTimeForAttack(float time) { m_timeForAttack = time; };

	int getRange() { return m_range; };
	int getDamage() { return m_damage; };
	float getAttackSpeed() { return m_attackSpeed; };
	WeaponType getWeaponType() { return m_weaponType; };
	bool getAllowAttack() { return m_allowAttack; };
	float getTimeToAllowAttack() { return m_timeToAllowAttack; };
	float getMaxTimeToAllowAttack() { return m_maxTimeToAllowAttack; };
	bool getAttacking() { return m_attacking; };
	float getMaxTimeForAttack() { return m_maxTimeForAttack; };
	float getTimeForAttack() { return m_timeForAttack; };

private:
	WeaponType m_weaponType;

	int m_range;
	int m_damage;
	float m_attackSpeed;

	bool m_allowAttack;
	float m_maxTimeToAllowAttack;
	float m_timeToAllowAttack;

	bool m_attacking;
	float m_maxTimeForAttack;
	float m_timeForAttack;
};