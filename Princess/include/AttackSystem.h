#pragma once

#include "System.h"
#include "WeaponComponent.h"
#include "MovementComponent.h"

class AttackSystem : public System
{
public:
	AttackSystem() {}

	void Update();
};