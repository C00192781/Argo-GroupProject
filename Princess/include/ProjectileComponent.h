#ifndef _PROJECTILECOMPONENT_H
#define _PROJECTILECOMPONENT_H

#include "Component.h"
class ProjectileComponent : public Component
{
public:
	ProjectileComponent()
	{
		m_type = "PJ";
		m_shooterType = "";
		m_baseSpeed = 100;
		m_timeToLive = 0;
	}

	ProjectileComponent(float speed)
	{
		m_type = "PJ";
		m_shooterType = "";
		m_baseSpeed = speed;
		m_timeToLive = 0;
	}

	~ProjectileComponent() {};

	void setShooterType(std::string type) { m_shooterType = type; }
	void setTimeToLive(float timeLeft) { m_timeToLive = timeLeft; }
	void setBaseSpeed(float speed) { m_baseSpeed = speed; }

	float getTimeToLive() { return m_timeToLive; }
	float getBaseSpeed() { return m_baseSpeed; }
	std::string getType() { return m_shooterType; }

private:
	float m_baseSpeed;
	float m_timeToLive;
	std::string m_shooterType;
};
#endif