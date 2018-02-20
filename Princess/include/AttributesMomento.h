#ifndef _ATTRIBUTESMOMENTO_H
#define _ATTRIBUTESMOMENTO_H

class AttributesMomento
{
private:

	int m_health;
	int m_maxHealth;

	int m_armour;
	int m_maxArmour;

	int m_movementSpeed;
	int m_maxMovementSpeed;

public:

	AttributesMomento(int health, int maxHealth, int armour, int maxArmour, int movement, int maxMovement) :m_health(health), m_maxHealth(maxHealth), m_armour(armour), m_maxArmour(maxArmour), m_movementSpeed(movement), m_maxMovementSpeed(maxMovement) {};
	~AttributesMomento() {};

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
};


#endif