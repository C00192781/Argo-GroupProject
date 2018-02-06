#ifndef _HEALTHSYSTEM_H
#define _HEALTHSYSTEM_H

#include "System.h"
#include "AttributesComponent.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "HeartComponent.h"
#include "HeartManagerComponent.h"

class HealthSystem : public System
{
private:
	void DamageEntity(int& damageCaused, int& armour, int& health);
	float timer;
public:
	HealthSystem();
	~HealthSystem();
	void Update() {};
	void Update(float deltaTime);
	void UpdateMaxHeartsUI(Entity * HeartManager, Entity* player);
	void UpdateHeartsUIStatus(Entity * HeartManager, Entity* player);
	void UpdateMaxArmourUI(Entity * HeartManager, Entity* player);
	void UpdateArmourUIStatus(Entity * HeartManager, Entity* player);
};
#endif