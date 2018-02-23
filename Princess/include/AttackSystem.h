#pragma once

#include "System.h"
#include "WeaponComponent.h"
#include "MovementComponent.h"
#include "ProjectileComponent.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"

class AttackSystem : public System
{
public:
	AttackSystem() {}
	AttackSystem(std::vector<Entity*>* projectiles);

	void Update() {}
	void Update(float deltaTime);

	std::vector<Entity*>* getProjectiles() { return m_projectiles; }
	void LoadComponent();
	void UnloadComponent(int x);
private:
	std::vector<Entity*>* m_projectiles;

	void setStaffOffset(WeaponComponent* weapon);
};


