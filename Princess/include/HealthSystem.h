#ifndef _HEALTHSYSTEM_H
#define _HEALTHSYSTEM_H

#include "System.h"
#include "AttributesComponent.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"

class HealthSystem : public System
{
private:
	std::vector<Entity*>m_player1Hearts;
	std::vector<Entity*>m_player2Hearts;
	std::vector<Entity*>m_player3Hearts;
	std::vector<Entity*>m_player4Hearts;

	std::vector<AttributesComponent*> m_attributeComponents;

	void DamageEntity(int& damageCaused, int& armour, int& health);
	float timer;
public:
	HealthSystem();
	~HealthSystem();
	void AddEntity(Entity * e, std::string tag);
	void Update() {};
	void Update(float deltaTime);
	void PlayerOneUpdate();
	void PlayerTwoUpdate();
	void PlayerThreeUpdate();
	void PlayerFourUpdate();
	void LoadComponent();
	void UnloadComponent(int x);
};
#endif