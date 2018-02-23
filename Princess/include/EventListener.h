#ifndef _EVENTLISTENER_H
#define _EVENTLISTENER_H

class EventListener
{
public:
	EventListener() {};
	bool LeftClick = false;
	bool RightClick = false;
	bool Space = false;
	bool W = false;
	bool A = false;
	bool S = false;
	bool D = false;
	bool Escape = false;
	bool TownToWorld = false;
	bool WorldToDungeon = false;
	bool WorldToEncounter = false;
	bool DungeonToWorld = false;
	bool EncounterToWorld = false;
	
	bool ToDungeon1 = false;
	bool ToDungeon2 = false;
	bool ToDungeon3 = false;
	bool ToDungeon4 = false;
	bool ToDungeon5 = false;
	bool ToWorldMap = false;

	bool host = false;
	bool connected = false;

	bool roll = false;
	bool WorldToTown = false;
	bool TownToShop = false;
	bool ShopToTown = false;
	bool MenuToWorld = false;
	bool MenuToOptions = false;
	bool OptionsToMenu = false;
};
#endif
