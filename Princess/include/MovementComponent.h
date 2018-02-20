#pragma once

#include "Component.h"
#include <iostream>

class MovementComponent : public Component
{
public:
	MovementComponent()
	{
		m_type = "movement";
		m_xVel = 0;
		m_yVel = 0;
		m_orientation = 0;
		m_lockOrientation = false;
		m_moving = false;
	}

	MovementComponent(int speed)
	{
		m_type = "movement";
		m_xVel = 0;
		m_yVel = 0;
		m_orientation = 0;
		m_lockOrientation = false;
		m_moving = false;
	}

	void setOrientation(float orientation) { m_orientation = orientation; };
	float getOrientation() { return m_orientation; };

	void setLockedOrientation(bool locked) { m_lockOrientation = locked; };
	bool getLockedOrientation() { return m_lockOrientation; };

	float getXVelocity() { return m_xVel; }
	float getYVelocity() { return m_yVel; }

	bool getMoving() { return m_moving; }

	void setVelocity(float x, float y) { m_xVel = x;  m_yVel = y; }
	void setXVelocity(float xVel) { m_xVel = xVel; }
	void setYVelocity(float yVel) { m_yVel = yVel; }

	void setMoving(bool moving) { m_moving = moving; }

	bool getRolling() { return m_rolling; }
	void setRolling(bool roll) { m_rolling = roll; }

private:
	float m_xVel;
	float m_yVel;
	bool m_rolling = false;

	float m_orientation;
	bool m_lockOrientation;

	bool m_moving;
};