#ifndef _BATTLEMAP_H
#define _BATTLEMAP_H

#include "Instance.h"
#include "SystemManager.h"
#include "BasicEnemy.h"

class BattleMap : public Instance
{
public:
	BattleMap(SystemManager * sm, StateManager * s, EventListener* listener);
	~BattleMap();

	void Generate(std::string type);

	void Update() {};
	void Update(float deltaTime);
	void Render();
private:
	EventListener* m_listener;
	SDL_Point m_startPoint;
	std::vector<Entity*> m_enemies; // points to the enemies in collision system
	float m_timeRemaining;
};
#endif