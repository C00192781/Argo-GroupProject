#ifndef _HEALTHSYSTEM_H
#define _HEALTHSYSTEM_H

#include "System.h"
#include "AttributesComponent.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "HeartComponent.h"

class HealthSystem : public System
{
public:
	HealthSystem();
	~HealthSystem();
	void Update();
	void UpdateMaxHearts();
	void UpdateHeartsStatus(Entity* player);
	void UpdateMaxArmour();
	void UpdateArmourStatus(Entity* player);

private:
	void DamageEntity(int& damageCaused, int& armour, int& health);

};
#endif