#ifndef _PROJECTILESYSTEM_H
#define _PROJECTILESYSTEM_H

#include "System.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"

#include <iostream>
class ProjectileSystem : public System
{
public:
	ProjectileSystem(float xPos, float yPos, float speed, float orientation);
	~ProjectileSystem();
	void Update();
	void velocityHandler(float orientation);
	void movementHandler(float speed);
	//void Collisions();
private:
	const float CONVERSION = 180 / 3.14159265359;
	int x;
	int y;
	float velocityX, velocityY;
	float m_orientation;
	float m_speed;

	float playerX, playerY;
	float playerWidth, playerHeight;
};
#endif