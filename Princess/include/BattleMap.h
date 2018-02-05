#ifndef _BATTLEMAP_H
#define _BATTLEMAP_H

#include "Instance.h"

class BattleMap : public Instance
{
public:
	BattleMap(SystemManager * sm, SDL_Renderer * sdlr, StateManager * s);
	~BattleMap();

	void Generate(std::string type);

	void Update();
	void Render();
};
#endif