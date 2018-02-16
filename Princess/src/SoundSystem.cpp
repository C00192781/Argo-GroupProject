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
				std::cout << "better out than in" << std::endl;
				soundKey = j;
				//m_entities.at(i)->GetComponents()->at(j)->
				/*static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(j)->)*/
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
			// set play is for testing
			if (test == false)
			{
				static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->setPlay();
				test = true;
			}


			std::string mode = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getMode();
			bool active = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getActive();

			if (mode == "play" && active == true)
			{
				int channel = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getChannel();
				Mix_Chunk* sound = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getSound();
				int loops = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getLoops();
				if (Mix_Playing(channel) == 0)
				{
					// plays sound
					Mix_PlayChannel(channel, sound, loops);
					static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->setActive(false);
				}
			}
			if (mode == "pause" && active == true)
			{
				int channel = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getChannel();
				Mix_Chunk* sound = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getSound();
				int loops = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getLoops();
				if (Mix_Playing(channel) == 1)
				{
					// pauses sound
					Mix_Pause(channel);
					static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->setActive(false);
				}
			}
			if (mode == "resume" && active == true)
			{
				int channel = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getChannel();
				Mix_Chunk* sound = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getSound();
				int loops = static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getLoops();
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
