#ifndef _AISYS_H
#define _AISYS_H

#include "System.h"
#include "AiLogicComponent.h"
#include "PositionComponent.h"
class AiSystem : public System
{
public:
	AiSystem();
	~AiSystem();
	void Update();
	void SetThingy(int x) { m_thingy = x; };
private:
	int m_thingy;
};
#endif