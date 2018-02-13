#pragma once

#include "Instance.h"

class DungeonMap : public Instance
{
public:
	DungeonMap(SystemManager * sm, StateManager * s, ResourceManager *rm);
	~DungeonMap();

	void Update() {};
	void Render() {};

	void generate();
private:
	ResourceManager * m_resourceManager;
};