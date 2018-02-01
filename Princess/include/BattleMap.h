#ifndef _BATTLEMAP_H
#define _BATTLEMAP_H

#include "Instance.h"

class BattleMap : public Instance
{
public:
	BattleMap() {};
	BattleMap(ResourceManager * r, SDL_Renderer * sdlr, EventListener * e, StateManager * s, int scale);
	~BattleMap();

	void Generate(std::string type);

	void Update();
	void Render();
};
#endif