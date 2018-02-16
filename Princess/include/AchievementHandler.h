#pragma once
#include "ConcreteObserver.h"
#include "ConcreteSubject.h"
#include "SystemManager.h"
#include "nlohmann\json.hpp"
#include "PositionComponent.h"

// for convenience
using json = nlohmann::json;

struct achievement
{
	bool activated; 
};

class AchievementHandler
{
public:
	AchievementHandler();
	AchievementHandler(SystemManager *s) { m_systemManager = s; Init(); };

	void Init();
	void HandleAchievements();
	void Animate(PositionComponent *positionComponent);
	void Removal(std::string identifier, float startTime);
	void Replace(); 
	void Generate(std::string identifier);

private:
	SystemManager * m_systemManager;
	// observers
	std::vector<ConcreteObserver> observers;
	// subject
	ConcreteSubject subject;

	json j;
	std::vector<Entity*> displayQueue;

	achievement A1, A2, A3, A4, A5, A6;
};
