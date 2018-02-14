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
#include "AttributesComponent.h"
#include "BasicEnemy.h"
#include "DecisionTree.h"

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
	void seek(int entityIndex, int pcKey, int mcKey, int seekKey, int attributeKey, float tarX, float tarY);
	void attack(int entityIndex, int attackKey, int mcKey);
	void normalise(float &x, float &y);
	float magnitude(float x, float y);
	void Wander(int i,int pcKey,int mcKey,int seekKey, int attributeKey);
	void LoadComponent();
	void UnloadComponent(int x);

private:

	std::vector<Character*> CharFactory;
	Character* characterFactory;

	DecisionTree* m_decisionTree = new DecisionTree(15, 5, 5, 5, 50);

	std::vector<AiLogicComponent*> m_aiLogicComponent;
	std::vector<SpriteComponent*> m_spriteComponent;
	std::vector<MovementComponent*> m_movementComponent;
	std::vector<SeekComponent*> m_seekComponent;
	std::vector<AttributesComponent*> m_attributesComponent;
	std::vector<AttackComponent*> m_attackComponent;
	std::vector<PositionComponent*> m_positionComponent;

	float m_time;
};
#endif