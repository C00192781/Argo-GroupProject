#pragma once
#include "Instance.h"

class GameOverInstance : public Instance
{
public:
	GameOverInstance(SystemManager * sm, StateManager * s);
	~GameOverInstance();
	void Update() {};
	void Update(float deltaTime);
	void Generate();
private:
	bool hasFaded;
	float timer;

};
