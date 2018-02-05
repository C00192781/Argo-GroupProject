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
	void Spawn(std::vector<Entity*> entities);
	void Spawn();
	std::vector<Entity*> getEntities();
private:
	std::vector<Character*> CharFactory;
	Character* characterFactory;
};
#endif