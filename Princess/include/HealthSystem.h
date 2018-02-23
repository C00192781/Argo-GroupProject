#ifndef _HEALTHSYSTEM_H
#define _HEALTHSYSTEM_H

#include "System.h"
#include "AttributesComponent.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "StateManager.h"

class HealthSystem : public System
{
private:
	std::vector<Entity*>m_player1Hearts;
	std::vector<Entity*>m_player2Hearts;
	std::vector<Entity*>m_player3Hearts;
	std::vector<Entity*>m_player4Hearts;

	std::vector<AttributesComponent*> m_attributeComponents;

	StateManager * m_stateManager;
	//void DamageEntity(int& damageCaused, int& armour, int& health);
	float timer;
public:
	HealthSystem(StateManager * sm);
	~HealthSystem();
	void AddEntity(Entity * e, std::string tag);
	void Update() {};
	void Update(float deltaTime);
	void PlayerOneUpdate();
	void PlayerTwoUpdate();
	void PlayerThreeUpdate();
	void PlayerFourUpdate();
	void CheckIfAllDead();
	void LoadComponent();
	void UnloadComponent(int x);
	void DeactivateHearts();
	void ActivateHearts();
	void HealAllEntities();
};
#endif