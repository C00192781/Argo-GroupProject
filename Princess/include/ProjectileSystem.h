#ifndef _PROJECTILESYSTEM_H
#define _PROJECTILESYSTEM_H

#include "System.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "MovementComponent.h"
#include "ProjectileComponent.h"


struct Vector2f
{
	float X;
	float Y;
};

#include <iostream>
class ProjectileSystem : public System
{
public:
	ProjectileSystem();
	~ProjectileSystem();
	void Update();
	Vector2f VelocityHandler(float orientation);
	Vector2f MovementHandler(float velocityX, float VelocityY, float speed);
	float CalculateSpeed(float buttonPressTime, float maxSpeed);
	//void Collisions();
private:
	const float CONVERSION = 180 / 3.14159265359;
	const float maxHoldTime = 3.0f;
	int x;
	int y;
	float velocityX, velocityY;
	//float m_orientation;
	float m_speed;

	float playerX, playerY;
	float playerWidth, playerHeight;
};
#endif