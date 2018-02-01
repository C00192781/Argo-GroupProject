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
	}

	MovementComponent(float speed)
	{
		m_type = "movement";
		m_xVel = 0;
		m_yVel = 0;
		m_speed = speed;
	}

	void setSpeed(int speed) { m_speed = speed; };
	float getSpeed() { return m_speed; };
	
	void setVelocity(float x, float y)
	{
		m_xVel = x;
		m_yVel = y;
	}

	float getXVelocity() { return m_xVel; }
	float getYVelocity() { return m_yVel; }

	void setXVelocity(float xVel) { m_xVel = xVel; }
	void setYVelocity(float yVel) { m_yVel = yVel; }

private:
	float m_speed;

	float m_xVel;
	float m_yVel;
};