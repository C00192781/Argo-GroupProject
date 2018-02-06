#ifndef _ATTRIBUTESCOMPONENT_H
#define _ATTRIBUTESCOMPONENT_H

#include <list>
#include "Component.h"
#include <iostream>

enum class ModiferTypes
{
	BLEED,
	CHILL,
	STUN,
	BURNING,
	HEALING,
	DAMAGE
};

struct Modifer
{
	ModiferTypes m_type;
	int m_amount;
	float m_duration;

	Modifer(ModiferTypes type = ModiferTypes::DAMAGE, int amount = 0, float duration = 0) :m_type(type), m_amount(amount), m_duration(duration) {};
};

class AttributesComponent : public Component
{
public:
	AttributesComponent()
	{
		m_type = "AC";

		m_armour = 5;
		m_maxArmour = 6;

		m_health = 26;
		m_maxHealth = 26;

		m_movementSpeed = 10;
		m_maxMovementSpeed = 10;

		m_modifers = new std::list<Modifer>();
	};
	AttributesComponent(int health, int maxHealth, int armour, int maxArmour, int movement, int maxMovement) :m_health(health), m_maxHealth(maxHealth), m_armour(armour), m_maxArmour(maxArmour), m_movementSpeed(movement), m_maxMovementSpeed(maxMovement) { m_type = "AC"; 
	};
	~AttributesComponent() 
	{
		m_modifers->clear();
		delete m_modifers;
	};

	int Armour() { return m_armour; };
	void Armour(int armour) { m_armour = armour; };

	int MaxArmour() { return m_maxArmour; };
	void MaxArmour(int armour) { m_maxArmour = armour; };

	int Health() { return m_health; };
	void Health(int health) { m_health = health; };

	int MaxHealth() { return m_maxHealth; };
	void MaxHealth(int health) { m_maxHealth = health; };

	int MovementSpeed() { return m_movementSpeed; };
	void MovementSpeed(int movementSpeed) { m_movementSpeed = movementSpeed; };

	int MaxMovementSpeed() { return m_maxMovementSpeed; };
	void MaxMovementSpeed(int movementSpeed) { m_maxMovementSpeed = movementSpeed; };

	std::list<Modifer> * Modifers() { return m_modifers; };

private:
	//The amount of armour the entity has
	int m_armour;
	//The max amount of armour the entity can have
	int m_maxArmour;

	//The amount of health the entity has
	int m_health;
	//The max amount of health the entity can have
	int m_maxHealth;

	//The movement speed the entity has
	int m_movementSpeed;
	//The max amount of movement speed the entity can have
	int m_maxMovementSpeed;

	std::list<Modifer> * m_modifers;
};
#endif
