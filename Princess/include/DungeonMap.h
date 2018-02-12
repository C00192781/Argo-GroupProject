#pragma once
#ifndef _DUNGEONMAP_H
#define _DUNGEONMAP_H

#include "Instance.h"

class DungeonMap : public Instance
{
public:
	DungeonMap(SystemManager * sm, StateManager * s);
	~DungeonMap();

	void Generate(std::string type);

	void Update();
	void Render();
};
#endif