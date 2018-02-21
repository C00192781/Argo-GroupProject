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

	//ProjectileComponent()
	//{
	//	m_type = "PJ";
	//	m_shooterType = " ";
	//	m_timeToLive = 0.0f;
	//	m_orientation = 0.0f;
	//	m_maxSpeed = 15;
	//	
	//};
	//
	//ProjectileComponent(float orientation, std::string shooter, float timeLeft, float buttonPress, float maxSpeed, bool alive)
	//{
	//	m_type = "PJ";
	//	m_shooterType = shooter; 
	//	m_timeToLive = timeLeft;
	//	m_orientation = orientation; 
	//	m_maxSpeed = maxSpeed;
	//	m_buttonPressTime = buttonPress;
	//	m_alive = alive;
	//};

	~ProjectileComponent() {};

	//void setMaxSpeed(float maxSpeed) { m_maxSpeed = maxSpeed; }
	//void setButtonPressTime(float buttonPress) { m_buttonPressTime = buttonPress; }
	//void setAliveStatus(bool alive) { m_alive = alive; }
	//void setOrientation(float orientation) { m_orientation = orientation; };
	void setShooterType(std::string type) { m_shooterType = type; }
	void setTimeToLive(float timeLeft) { m_timeToLive = timeLeft; }
	void setBaseSpeed(float speed) { m_baseSpeed = speed; }

	//float getOrientation() { return m_orientation;  }
	//float getMaxSpeed() { return m_maxSpeed; }
	//float getButtonPressTime() { return m_buttonPressTime; }
	float getTimeToLive() { return m_timeToLive; }
	float getBaseSpeed() { return m_baseSpeed; }
	std::string getType() { return m_shooterType; }
	std::string getShooterType() { return m_shooterType; }

	//bool getAliveStatus() { return m_alive; }


private:
	float m_baseSpeed;
	//float m_orientation;
	float m_timeToLive;
	//float m_buttonPressTime;
	std::string m_shooterType;
	//bool m_alive;
};
#endif