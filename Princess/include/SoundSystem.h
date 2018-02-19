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

	void LoadComponent() {};
	void UnloadComponent(int x) {};
private:
	bool assigned;
	bool test = false;
	std::vector<SoundComponent*> sounds;
	std::vector<MusicComponent*> music;
	ResourceManager * m_resourceManager;
	int timer = 0;
};
