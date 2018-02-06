#ifndef _HEALTHSYSTEM_H
#define _HEALTHSYSTEM_H

#include "System.h"
#include "AttributesComponent.h"
#include "SpriteComponent.h"
#include "RectangleComponent.h"
#include "HeartComponent.h"

class HealthSystem : public System
{
public:
	HealthSystem();
	~HealthSystem();
	void Update();
	void UpdateMaxHearts();
	void UpdateHeartsStatus(std::shared_ptr<Entity> player);
	void UpdateMaxArmour();
	void UpdateArmourStatus(std::shared_ptr<Entity> player);

private:
	void DamageEntity(int& damageCaused, int& armour, int& health);

};
#endif