#ifndef _AISYS_H
#define _AISYS_H
#include "Character.h"
#include "System.h"
#include "AiLogicComponent.h"
#include "PositionComponent.h"
#include "Princess.h"

class AiSystem : public System
{
public:
	AiSystem();
	~AiSystem();
	void Update();
	void SetThingy(int x) { m_thingy = x; };
	void Spawn(std::vector<Entity*> entities);
	void Spawn();
private:
	int m_thingy;
	std::vector<Character*> CharFactory;
	Character* characterFactory;
};
#endif