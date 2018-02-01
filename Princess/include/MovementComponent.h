#pragma once

#include "Component.h"

class MovementComponent : public Component 
{
public:
	MovementComponent() 
	{
		m_type = "movement";
		m_vel = { 0, 0 };
		m_maxSpeed = 0;
	}

	MovementComponent(int maxSpeed)
	{
		m_vel = { 0,0 };
		m_maxSpeed = maxSpeed;
	}

	SDL_Point getVelocity() { return m_vel; }
	void setVelocity(SDL_Point vel) { m_vel = vel; }
	void setXVeclocity(float xVel) { m_vel.x = xVel; }
	void setYVeclocity(float yVel) { m_vel.y = yVel; }

private:
	int m_maxSpeed;

	SDL_Point m_vel;
};