#pragma once

#include "Component.h"

class AttackComponent : public Component
{
public:
	AttackComponent() {}

	AttackComponent(int range, int damage, float attackSpeed)
	{
		m_type = "attack";
		m_range = range;
		m_damage = damage;
		m_attackSpeed = attackSpeed;
	}

	int getRange() { return m_range; };
	int getDamage() { return m_damage; };
	float getAttackSpeed() { return m_attackSpeed; };

private:
	int m_range;
	int m_damage;
	float m_attackSpeed;
};