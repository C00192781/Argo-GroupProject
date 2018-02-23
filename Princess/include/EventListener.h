#ifndef _EVENTLISTENER_H
#define _EVENTLISTENER_H

class EventListener
{
public:
	EventListener() {};
	// Mouse & Keyboard
	bool LeftClick = false;
	bool RightClick = false;
	bool Space = false;
	bool W = false;
	bool A = false;
	bool S = false;
	bool D = false;
	bool Escape = false;

	// Controller Triggers 
	// range of 0 to 32767
	int LeftTrigger = 0;
	int RightTrigger = 0;

	// Sticks 
	// range of -32767 to 32767
	float LeftStickX = 0;
	float LeftStickY = 0;
	float RightStick = 0;

	// Buttons
	bool AButton = false;
	bool BButton = false;
	bool YButton = false;
	bool XButton = false;
	bool LeftShoulder = false;
	bool RightShoulder = false;
	bool UpButton = false;
	bool DownButton = false;
	bool LeftButton = false;
	bool RightButton = false;
	bool StartButton = false;
	bool BackButton = false;
	bool GuideButton = false;

	bool controllerActivated = false;

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
	bool ToTown = false;

	bool ChangedWeapon = false;
	bool ChangedArmor = false;

	bool host = false;
	bool connected = false;

	bool connectFromMenu = false;

	bool roll = false;

	bool WorldToTown = false;
	bool TownToShop = false;
	bool ShopToTown = false;
	bool MenuToWorld = false;
	bool MenuToOptions = false;
	bool OptionsToMenu = false;
};
#endif
