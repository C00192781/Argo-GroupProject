#pragma once

#include "System.h"
#include "SoundComponent.h"
#include "MusicComponent.h"
#include "ResourceManager.h"

class SoundSystem : public System
{
public:
	SoundSystem() {}
	SoundSystem(ResourceManager * resourceManager);

	void assignSounds(); 
	void Update();

	int GetSoundVolume();
	void SetSoundVolume(int volume);

	int GetMusicVolume();
	void SetMusicVolume(int volume);

	void LoadComponent() {};
	void UnloadComponent(int x) {};
private:
	bool assigned;
	bool test = false;
	std::vector<SoundComponent*> sounds;
	std::vector<MusicComponent*> music;
	ResourceManager * m_resourceManager;
	int timer = 0;
	int m_soundVolume = 100;
	int m_musicVolume = 100;
};
