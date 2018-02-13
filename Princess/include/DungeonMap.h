#pragma once

#include "Instance.h"
#include "DungeonTileFactory.h"

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