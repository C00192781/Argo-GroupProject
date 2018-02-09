#ifndef _PROJECTILECOMPONENT_H
#define _PROJECTILECOMPONENT_H

#include "Component.h"
class ProjectileComponent : public Component
{
public:
	ProjectileComponent()
	{
		m_type = "PJ";
		shooterType = " ";
		timeToLive = 0.0f;
		m_orientation = 0.0f;
		m_maxSpeed = 15;
		
	};

	ProjectileComponent(float orientation, std::string shooter, float timeLeft, float buttonPress, float maxSpeed)
	{
		m_type = "PJ";
		shooterType = shooter; 
		timeToLive = timeLeft;
		m_orientation = orientation; 
		m_maxSpeed = maxSpeed;
		buttonPressTime = buttonPress;
	};

	~ProjectileComponent() {};


	void setOrientation(float orientation) { m_orientation = orientation; };
	void setShooterType(std::string type) { shooterType = type; }
	void setTimeToLive(float timeLeft) { timeToLive = timeLeft; }
	void setMaxSpeed(float maxSpeed) { m_maxSpeed = maxSpeed; }
	void setButtonPressTime(float buttonPress) { buttonPressTime = buttonPress; }

	float getOrientation() { return m_orientation;  }
	float getTimeToLive() { return timeToLive; }
	float getMaxSpeed() { return m_maxSpeed; }
	float getButtonPressTime() { return buttonPressTime; }
	std::string getType() { return shooterType;  }

private:
	float m_maxSpeed;
	float m_orientation;
	float timeToLive;
	float buttonPressTime;
	std::string shooterType;

};
#endif
