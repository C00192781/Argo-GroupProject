#ifndef _HEALTHSYSTEM_H
#define _HEALTHSYSTEM_H

#include "System.h"
#include "AttributesComponent.h"
class HealthSystem : public System
{
public:
	HealthSystem();
	~HealthSystem();
	void Update();
	void DamageEntity(int damageCaused, int armour, int health);
private:


};
#endif