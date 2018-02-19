#pragma once

#include "Component.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class SoundComponent : public Component
{
public:
	SoundComponent() {}

	SoundComponent(std::string identifier, std::string mode, bool active, int channel, int loops, int volume)
	{
		m_type = "sound";
		m_identifier = identifier;
		m_mode = mode;
		m_active = active;
		m_channel = channel;
		m_loops = loops;
		m_volume = volume;
		m_volumeSetter = true;
	}

	void setPlay() { m_mode = "play";  m_active = true; }
	void setPause() { m_mode = "pause";  m_active = true; }
	void setResume() { m_mode = "resume";  m_active = true; }
	void setSound(Mix_Chunk* sound) { m_sound = sound; }
	void setActive(bool active) { m_active = active; }
	void setVolume(int volume) { m_volume = volume; m_volumeSetter = true; }
	void setVolumeSetter(bool setter) { m_volumeSetter = setter; }

	Mix_Chunk* getSound() { return m_sound; }
	std::string getMode() { return m_mode; }
	std::string getIdentifier() { return m_identifier; }
	int getChannel() { return m_channel; }
	int getLoops() { return m_loops; }
	bool getActive() { return m_active; }
	bool getVolumeSetter() { return m_volumeSetter; }
	int getVolume() { return m_volume; }

private:
	Mix_Chunk *m_sound;
	std::string m_identifier;
	std::string m_mode;
	bool m_active;
	bool m_volumeSetter;
	int m_channel;
	int m_loops;
	int m_volume;
};
