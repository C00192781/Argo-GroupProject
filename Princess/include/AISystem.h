#ifndef _AISYS_H
#define _AISYS_H
#include "Character.h"
#include "System.h"
#include "AiLogicComponent.h"
#include "PositionComponent.h"
#include "Princess.h"
#include "MovementComponent.h"
#include "SeekComponent.h"
#include "AttackComponent.h"

class AiSystem : public System
{
public:
	AiSystem();
	~AiSystem();
	void Update();
	void Update(float deltaTime);
	void Spawn(std::string id);
	void Spawn();
	std::vector<Entity*> getEntities();
	void seek(int entityIndex, int pcKey, int mcKey, int seekKey);
	void attack(int entityIndex, int attackKey, int mcKey);
	void normalise(float &x, float &y);
	float magnitude(float x, float y);
	void Wander(int i,int pcKey,int mcKey,int seekKey);
private:
	std::vector<Character*> CharFactory;
	Character* characterFactory;
	float m_time;
};
#endif