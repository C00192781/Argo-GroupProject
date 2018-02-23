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
#include "AStar.h"

#include "WeaponComponent.h"
class AiSystem : public System
{
public:
	AiSystem(AStar * aStar);
	~AiSystem();
	void Update();
	void Update(float deltaTime, std::vector<Entity*> players);
	void Spawn(std::string id);
	void Spawn();
	std::vector<Entity*> getEntities();

	void seek(int entityIndex, int pcKey, int mcKey, int seekKey, int attributeKey, float tarX, float tarY, int behaviour, string tag);
	void attack(int entityIndex, int attackKey, int mcKey, string tag);

	void normalise(float &x, float &y);
	float magnitude(float x, float y);
	void Wander(int i,int pcKey,int mcKey,int seekKey, int attributeKey);
	void LoadComponent();
	void UnloadComponent(int x);

private:

	std::vector<Character*> CharFactory;
	Character* characterFactory;


	DecisionTree* m_decisionTree = new DecisionTree(15, 5, 5, 5, 50, 50, 100); //debug values, overwrite in update -> pathNode
	AStar *m_aStar;

	std::vector<AiLogicComponent*> m_aiLogicComponent;
	std::vector<SpriteComponent*> m_spriteComponent;
	std::vector<MovementComponent*> m_movementComponent;
	std::vector<SeekComponent*> m_seekComponent;
	std::vector<AttributesComponent*> m_attributesComponent;
	std::vector<AttackComponent*> m_attackComponent;
	std::vector<PositionComponent*> m_positionComponent;

	
	std::vector<Entity*> m_playerEntities;
	std::vector<AttributesComponent*> m_attribComp;
	std::vector<Entity*> m_compIDVec;

	int m_health;
	int m_MAXHEALTH;

	float m_time;
	int timer;
	int currentPlayer;
};
#endif