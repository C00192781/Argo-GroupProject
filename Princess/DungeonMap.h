#pragma once
#ifndef _BATTLEMAP_H
#define _BATTLEMAP_H

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