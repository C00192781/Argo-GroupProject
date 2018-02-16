#pragma once

#include "Component.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class MusicComponent : public Component
{
public:
	MusicComponent() {}

	MusicComponent(std::string identifier, std::string mode, bool active, int channel, int loops)
	{
		m_type = "sound";
		m_identifier = identifier;
		m_mode = mode;
		m_active = active;
		m_channel = channel;
		m_loops = loops;
	}

	void setPlay() { m_mode = "play";  m_active = true; }
	void setPause() { m_mode = "pause";  m_active = true; }
	void setResume() { m_mode = "resume";  m_active = true; }
	void setSound(Mix_Music* sound) { m_sound = sound; }
	void setActive(bool active) { m_active = active; }

	Mix_Music* getSound() { return m_sound; }
	std::string getMode() { return m_mode; }
	std::string getIdentifier() { return m_identifier; }
	int getChannel() { return m_channel; }
	int getLoops() { return m_loops; }
	bool getActive() { return m_active; }


private:

	Mix_Music * m_sound;
	std::string m_identifier;
	std::string m_mode;
	bool m_active;
	int m_channel;
	int m_loops;
};
