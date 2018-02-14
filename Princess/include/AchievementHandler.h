#pragma once
#include "ConcreteObserver.h"
#include "ConcreteSubject.h"
#include "SystemManager.h"
#include "nlohmann\json.hpp"

// for convenience
using json = nlohmann::json;

class AchievementHandler
{
public:
	AchievementHandler();
	AchievementHandler(SystemManager *s) { m_systemManager = s; };

	void Init();
	void HandleAchievements();

private:
	SystemManager * m_systemManager; 
	std::vector<ConcreteObserver> observers;
	ConcreteSubject subject;

	bool activated1, activated2, activated3, activated4,
		activated5, activated6;

	json j;
};