#pragma once

#include "Component.h"

class MovementComponent : public Component 
{
public:
	MovementComponent() 
	{
		m_type = "movement";
		m_vel = { 0, 0 };
		m_speed = 0;
	}

	MovementComponent(int speed)
	{
		m_type = "movement";
		m_vel = { 0,0 };
		m_speed = speed;
	}

	void setSpeed(int speed) { m_speed = speed; };
	int getSpeed() { return m_speed; };

	SDL_Point getVelocity() { return m_vel; }
	void setVelocity(SDL_Point vel) { m_vel = vel; }
	void setXVeclocity(float xVel) { m_vel.x = xVel; }
	void setYVeclocity(float yVel) { m_vel.y = yVel; }

private:
	int m_speed;

	SDL_Point m_vel;
};