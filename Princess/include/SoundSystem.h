#pragma once

#include "System.h"
#include "SoundComponent.h"
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
	std::vector<SoundComponent> sounds;
	ResourceManager * m_resourceManager;
	int timer = 0;
};
