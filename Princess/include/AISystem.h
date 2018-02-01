#pragma once

#include "System.h"
#include "SeekComponent.h"
#include "PositionComponent.h"
#include "MovementComponent.h"

class AISystem : public System
{
public:
	AISystem() {}

	void Update();
private:
	void seek(int entityIndex, int pcKey, int mcKey, int seekKey);

	void normalise(float &x, float &y);
	float magnitude(float x, float y);
	//float magnitude(float &x1, float &y1, float &x2, float &y2);
};