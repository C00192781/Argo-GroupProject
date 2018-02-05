#ifndef _WORLDMAP_H
#define _WORLDMAP_H

#include "Instance.h"
#include "WorldTileFactory.h"

class WorldMap : public Instance
{
public:
	WorldMap(SystemManager * sm, StateManager * s);
	~WorldMap();

	void Generate(int width, int height, int chaosFactor);
	void Load();

	void Update();
	void Render();

private:
	int m_chaos;
};
#endif
