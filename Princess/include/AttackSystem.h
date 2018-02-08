#pragma once

#include "System.h"
#include "WeaponComponent.h"
#include "MovementComponent.h"

class AttackSystem : public System
{
public:
	AttackSystem() {}
	AttackSystem(std::vector<Entity*>* projectiles);

	void Update();

	std::vector<Entity*>* getProjectiles() { return m_projectiles; }
private:
	std::vector<Entity*>* m_projectiles;
};