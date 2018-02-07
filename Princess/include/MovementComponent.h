#pragma once

#include "Component.h"

class MovementComponent : public Component 
{
public:
	MovementComponent() 
	{
		m_type = "movement";
		m_xVel = 0;
		m_yVel = 0;
		m_speed = 0;
		m_orientation = 0;
		m_lockOrientation = false;
	}

	MovementComponent(int speed)
	{
		m_type = "movement";
		m_xVel = 0;
		m_yVel = 0;
		m_speed = speed;
		m_orientation = 0;
		m_lockOrientation = false;
	}

	//void setSpeed(int speed) { m_speed = speed; };
	//int getSpeed() { return m_speed; };

	void setOrientation(float orientation) { m_orientation = orientation; };
	float getOrientation() { return m_orientation; };

	void setLockedOrientation(bool locked) { m_lockOrientation = locked; };
	bool getLockedOrientation() { return m_lockOrientation; };

	float getXVelocity() { return m_xVel; }
	//float* getXVelocityRef() { return &m_yVel; }
	float getYVelocity() { return m_yVel; }
	//float* getYVelocityRef() { return &m_yVel; }
	void setVelocity(float x, float y) { m_xVel = x;  m_yVel = y; }
	void setXVelocity(float xVel) { m_xVel = xVel; }
	void setYVelocity(float yVel) { m_yVel = yVel; }

private:
	int m_speed;

	float m_xVel;
	float m_yVel;

	float m_orientation;
	bool m_lockOrientation;
};