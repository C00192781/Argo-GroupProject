#ifndef _ATTRIBUTESCOMPONENT_H
#define _ATTRIBUTESCOMPONENT_H

#include <list>
#include "Component.h"
#include "AttributesMomento.h"
#include <iostream>

class AttributesComponent : public Component
{
public:
	AttributesComponent()
	{
		m_type = "attribute";

		m_armour = 5;
		m_maxArmour = 6;

		m_health = 26;
		m_maxHealth = 26;

		m_movementSpeed = 10;
		m_maxMovementSpeed = 10;

		m_additiveArmour = 0;
		m_additiveHealth = 0;
		m_additiveMovementSpeed = 0;
	};


	AttributesComponent(int health, int maxHealth, int armour, int maxArmour, int movement, int maxMovement) :m_health(health), m_maxHealth(maxHealth), m_armour(armour), m_maxArmour(maxArmour), m_movementSpeed(movement), m_maxMovementSpeed(maxMovement) 
	{ 
		m_type = "attribute";
		momento = new AttributesMomento(health, maxHealth, armour, maxArmour, movement, maxMovement, 0, 0, 0);
		m_additiveArmour = 0;
		m_additiveHealth = 0;
		m_additiveMovementSpeed = 0;
	};

	~AttributesComponent()
	{

	};

	int Armour() { return m_armour; };
	void Armour(int armour) { m_armour = armour; };

	int Health() { return m_health; };
	void Health(int health) { m_health = health; };

	int MovementSpeed() { return m_movementSpeed; };
	void MovementSpeed(int movementSpeed) { m_movementSpeed = movementSpeed; };

	int MaxArmour() { return m_maxArmour + m_additiveArmour; };
	void MaxArmour(int armour) { m_maxArmour = armour; };

	int MaxHealth() { return m_maxHealth + m_additiveHealth; };
	void MaxHealth(int health) { m_maxHealth = health; };

	int MaxMovementSpeed() { return m_maxMovementSpeed + m_additiveMovementSpeed; };
	void MaxMovementSpeed(int movementSpeed) { m_maxMovementSpeed = movementSpeed; };

	
	void Save()
	{
		delete momento;
		momento = new AttributesMomento(m_health, m_maxHealth, m_armour, m_maxArmour, m_movementSpeed, m_maxMovementSpeed, m_additiveArmour, m_additiveHealth,m_additiveMovementSpeed);
	}

	void Revert()
	{
		m_health = momento->Health();
		m_maxHealth = momento->MaxHealth();
		m_armour = momento->Armour();
		m_maxArmour = momento->MaxArmour();
		m_movementSpeed = momento->MovementSpeed();
		m_maxMovementSpeed = momento->MaxMovementSpeed();
		m_additiveArmour = momento->AdditiveArmour();
		m_additiveHealth = momento->AdditiveHealth();
		m_additiveMovementSpeed = momento->AdditiveMovementSpeed();
	}

	void AdditiveArmour(int x) { m_additiveArmour = x; };
	int AdditiveArmour() { return m_additiveArmour; }
	void AdditiveHealth(int x) { m_additiveHealth = x; };
	int AdditiveHealth() { return m_additiveHealth; }
	void AdditiveMovement(int x) { m_additiveMovementSpeed = x; };



private:
	int m_armour;
	int m_maxArmour;
	int m_additiveArmour;

	int m_health;
	int m_maxHealth;
	int m_additiveHealth;

	int m_movementSpeed;
	int m_maxMovementSpeed;

	//holds previous state of the object
	AttributesMomento * momento;

	int m_additiveMovementSpeed;

};
#endif