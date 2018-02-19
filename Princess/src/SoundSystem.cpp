#include "SoundSystem.h"

SoundSystem::SoundSystem(ResourceManager * resourceManager)
{
	m_resourceManager = resourceManager;
	assigned = false;
}

void SoundSystem::assignSounds()
{
	/*for (std::vector<SoundComponent>::iterator it = sounds.begin(); it != sounds.end(); ++it)
	{
		(*it).setSound(m_resourceManager->GetSound((*it).getIdentifier()));
	}*/
	for (int i = 0; i < m_entities.size(); i++)
	{
		int soundKey = -1;
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "sound")
			{
				soundKey = j;
			}
		}

		if (soundKey >= 0)
		{
			Mix_Chunk* sound = m_resourceManager->GetSound(static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getIdentifier());
			static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->setSound(sound);
		}
	}
}

void SoundSystem::Update()
{
	timer++;
	if (assigned == false)
	{
		assignSounds();
		assigned = true;
	}
	

	for (int i = 0; i < m_entities.size(); i++)
	{
		int soundKey = -1;
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "sound")
			{
				soundKey = j;
			}
		}

		if (soundKey >= 0)
		{
			// this is for testing
			if (test == false)
			{
				static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->setPlay();
				test = true;
			}
			if (timer > 100)
			{
				static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->setPause();
			}
			if (timer > 150)
			{
				static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->setResume();
			}

			bool active = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getActive();
			bool volumeSetter = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getVolumeSetter();

			if (volumeSetter == true)
			{
				int channel = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getChannel();
				Mix_Chunk* sound = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getSound();
				int volume = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getVolume();

				Mix_Volume(channel, MIX_MAX_VOLUME / 100 * volume);
				static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->setVolumeSetter(false);
				volumeSetter = false;
			}
			
			if (active == true)
			{
				std::string mode = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getMode();
				int channel = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getChannel();
				Mix_Chunk* sound = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getSound();
				int loops = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getLoops();

				if (mode == "play")
				{
					if (Mix_Playing(channel) == 0)
					{
						// plays sound
						Mix_PlayChannel(channel, sound, loops);
						static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->setActive(false);
					}
				}
				else if (mode == "pause")
				{
					if (Mix_Playing(channel) == 1)
					{
						// pauses sound
						Mix_Pause(channel);
						static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->setActive(false);
					}
				}
				else if (mode == "resume")
				{
					if (Mix_Paused(channel) == 1)
					{
						// resumes sound
						Mix_Resume(channel);
						static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->setActive(false);
					}
				}	
			}
		}
	}
}
