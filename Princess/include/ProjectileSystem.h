#ifndef _PROJECTILESYSTEM_H
#define _PROJECTILESYSTEM_H

#include "System.h"
#include "RectangleComponent.h"
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
	std::vector<Entity*>* getEntities();

private:
	const float CONVERSION = 180 / 3.14159265359;
	const float maxHoldTime = 3.0f;
};
#endif