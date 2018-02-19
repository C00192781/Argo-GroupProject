#ifndef _WORLDMAP_H
#define _WORLDMAP_H

#include "Instance.h"
#include <time.h>
#include "WorldTileFactory.h"

class WorldMap : public Instance
{
public:
	WorldMap(SystemManager * sm, StateManager * s, EventListener* listener);
	~WorldMap();

	void Generate(int width, int height, int chaosFactor);
	void Load();

	void Update();
	void Render() {};

private:
	int m_chaos;

	void ApplyLake(std::vector<std::vector<std::string>>* map, int x, int y, int width);

	void ApplyDesert(std::vector<std::vector<std::string>>* map, int x, int y, int width);
	void ApplySnowField(std::vector<std::vector<std::string>>* map, int x, int y, int width);

	//Planes Stuff
	void ApplyForest(std::vector<std::vector<std::string>>* map, int x, int y, int width);
	void ApplyMeadow(std::vector<std::vector<std::string>>* map, int x, int y, int width);

	//Desert Stuff
	void ApplyDune(std::vector<std::vector<std::string>>* map, int x, int y, int width);
	void ApplyRock(std::vector<std::vector<std::string>>* map, int x, int y, int width);

	//Snow Stuff
	void ApplySnowDune(std::vector<std::vector<std::string>>* map, int x, int y, int width);
	void ApplyGlacier(std::vector<std::vector<std::string>>* map, int x, int y, int width);

	EventListener* m_listener;
	SDL_Point m_randomEncounterLocation;
};
#endif
