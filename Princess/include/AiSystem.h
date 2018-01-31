#pragma once
#include "PositionComponent.h"
//include health components blah blah
#include "Entity.h"

class AISystem
{
private:
	std::vector<Entity *> entities;

public:
	AISystem() {};
	void addEntity(Entity *e);
	void update();

};