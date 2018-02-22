#ifndef _STATEMANAGER_H
#define _STATEMANAGER_H

class StateManager
{
public:
	bool MainMenu = false;
	bool Options = false;
	bool Battle = false;
	bool StartGame = false;
	bool ExitGame = false;
	bool decreaseSound = false;
	bool increaseSound = false;
	bool decreaseMusic = false;
	bool increaseMusic = false;
	bool SaveGame = false;
	bool LoadGame = false;
	bool GameOver = false;
	bool ReturnToWorld = false;
};
#endif