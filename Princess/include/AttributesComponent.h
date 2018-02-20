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
	//Modifer() 
	//{ 
	//	m_type = ModiferTypes::DAMAGE;
	//	m_amount = 0;
	//	m_duration = 0;
	//};

	Modifer(ModiferTypes type = ModiferTypes::DAMAGE, int amount = 0, float duration = 0) :m_type(type), m_amount(amount), m_duration(duration) {};
};

class AttributesComponent : public Component
{
public:
	AttributesComponent()
	{
		m_type = "attribute";

		//std::cout << m_type << std::endl;

		m_armour = 5;
		m_maxArmour = 6;

		m_health = 5;
		m_maxHealth = 5;

		m_movementSpeed = 10;
		m_maxMovementSpeed = 10;

		m_modifers = new std::list<Modifer>();
	};


	AttributesComponent(int health, int maxHealth, int armour, int maxArmour, int movement, int maxMovement) :m_health(health), m_maxHealth(maxHealth), m_armour(armour), m_maxArmour(maxArmour), m_movementSpeed(movement), m_maxMovementSpeed(maxMovement) { m_type = "attribute"; };

	~AttributesComponent() 
	{
		m_modifers->clear();
		delete m_modifers;
	};

	int Armour() { return m_armour; };
	void Armour(int armour) { m_armour = armour; };

	int Health() { return m_health; };
	void Health(int health) { m_health = health; };

	int MovementSpeed() { return m_movementSpeed; };
	void MovementSpeed(int movementSpeed) { m_movementSpeed = movementSpeed; };

	int MaxArmour() { return m_maxArmour; };
	void MaxArmour(int armour) { m_maxArmour = armour; };

	int MaxHealth() { return m_maxHealth; };
	void MaxHealth(int health) { m_maxHealth = health; };

	int MaxMovementSpeed() { return m_maxMovementSpeed; };
	void MaxMovementSpeed(int movementSpeed) { m_maxMovementSpeed = movementSpeed; };

	std::list<Modifer> * Modifers() { return m_modifers; };

private:
	int m_armour;
	int m_maxArmour;

	int m_health;
	int m_maxHealth;

	int m_movementSpeed;
	int m_maxMovementSpeed;

	std::list<Modifer> * m_modifers;
};
#endif
