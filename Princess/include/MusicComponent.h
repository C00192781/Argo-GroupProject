#pragma once

#include "Component.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class MusicComponent : public Component
{
public:
	MusicComponent() {}

	MusicComponent(std::string identifier, std::string mode, bool active, int loops, int volume)
	{
		m_type = "music";
		m_identifier = identifier;
		m_mode = mode;
		m_active = active;
		m_loops = loops;
		m_volume = volume;
		m_volumeSetter = true;
	}

	void setPlay() { m_mode = "play";  m_active = true; }
	void setPause() { m_mode = "pause";  m_active = true; }
	void setResume() { m_mode = "resume";  m_active = true; }
	void setMusic(Mix_Music* sound) { m_music = sound; }
	void setActive(bool active) { m_active = active; }
	void setVolume(int volume) { m_volume = volume; m_volumeSetter = true; }
	void setVolumeSetter(bool setter) { m_volumeSetter = setter; }

	Mix_Music* getMusic() { return m_music; }
	std::string getMode() { return m_mode; }
	std::string getIdentifier() { return m_identifier; }
	int getLoops() { return m_loops; }
	bool getActive() { return m_active; }
	bool getVolumeSetter() { return m_volumeSetter; }
	int getVolume() { return m_volume; }
	void setIdentifier(std::string x) { m_identifier = x; };

private:
	Mix_Music *m_music;
	std::string m_identifier;
	std::string m_mode;
	bool m_active;
	bool m_volumeSetter;
	int m_loops;
	int m_volume;
};

