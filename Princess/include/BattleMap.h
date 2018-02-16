#ifndef _BATTLEMAP_H
#define _BATTLEMAP_H

#include "Instance.h"
#include "SystemManager.h"

class BattleMap : public Instance
{
public:
	BattleMap(SystemManager * sm, StateManager * s);
	~BattleMap();

	void Generate(std::string type);

	void Update();
	void Render();
};
#endif