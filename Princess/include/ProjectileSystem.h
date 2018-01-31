#ifndef _PROJECTILESYSTEM_H
#define _PROJECTILESYSTEM_H

#include "System.h"
#include "PositionComponent.h"

#include <iostream>
class ProjectileSystem : public System
{
public:
	ProjectileSystem(float xPos, float yPos, float speed, float orientation);
	~ProjectileSystem();
	void Update();

	const float CONVERSION = 180 / 3.14159265359;
	int x = 300;
	int y = 300;
	float velocityX, velocityY = 0;
	float m_orientation;
	float m_speed;
	float tempX, tempY;
private:
	
};
#endif