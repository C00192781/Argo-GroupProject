#include "SoundSystem.h"

SoundSystem::SoundSystem(ResourceManager * resourceManager)
{
	m_resourceManager = resourceManager;
	assigned = false;
}

void SoundSystem::assignSounds()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		int soundKey = -1;
		int musicKey = -1;
		int count = 0;
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
		
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "sound")
			{
				soundKey = j;
				Mix_Chunk* sound = m_resourceManager->GetSound(static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getIdentifier());
				std::cout << static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->getIdentifier() << std::endl;
				static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey))->setSound(sound);
				sounds.push_back(static_cast<SoundComponent*>(m_entities.at(i)->GetComponents()->at(soundKey)));
			}
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "music")
			{
				musicKey = j;
				Mix_Music* mus = m_resourceManager->GetMusic(static_cast<MusicComponent*>(m_entities.at(i)->GetComponents()->at(musicKey))->getIdentifier());
				static_cast<MusicComponent*>(m_entities.at(i)->GetComponents()->at(musicKey))->setMusic(mus);
				music.push_back(static_cast<MusicComponent*>(m_entities.at(i)->GetComponents()->at(musicKey)));
			}
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
	for (std::vector<SoundComponent*>::iterator it = sounds.begin(); it != sounds.end(); ++it)
	{
		if ((*it)->getVolumeSetter() == true)
		{
			Mix_Volume((*it)->getChannel(), MIX_MAX_VOLUME / 100 * (*it)->getVolume()*(m_soundVolume/100.0f));
			(*it)->setVolumeSetter(false);
		}

		if ((*it)->getMode() == "play" && (*it)->getActive() == true)
		{
			if (Mix_Playing((*it)->getChannel()) == 0)
			{
				// plays sound
				Mix_PlayChannel((*it)->getChannel(), (*it)->getSound(), (*it)->getLoops());
				(*it)->setActive(false);
			}
		}
		if ((*it)->getMode() == "pause" && (*it)->getActive() == true)
		{
			if (Mix_Playing((*it)->getChannel()) == 1)
			{
				// pauses sound
				Mix_Pause((*it)->getChannel());
				(*it)->setActive(false);
			}
		}
		if ((*it)->getMode() == "resume" && (*it)->getActive() == true)
		{
			if (Mix_Paused((*it)->getChannel()) == 1)
			{
				// resumes sound
				Mix_Resume((*it)->getChannel());
				(*it)->setActive(false);
			}
		}

	}

	for (std::vector<MusicComponent*>::iterator it = music.begin(); it != music.end(); ++it)
	{
		if ((*it)->getVolumeSetter() == true)
		{
			Mix_VolumeMusic(MIX_MAX_VOLUME / 100 * (*it)->getVolume()*(m_musicVolume/100.0f));
			(*it)->setVolumeSetter(false);
		}

		if ((*it)->getActive() == true && (*it)->getMode() == "play")
		{
			if (Mix_PlayingMusic() == 0)
			{
				if (Mix_PausedMusic() == 0)
				{
					Mix_PlayMusic((*it)->getMusic(), (*it)->getLoops());
					(*it)->setActive(false);
				}
			}
		}
		else if ((*it)->getActive() == true && (*it)->getMode() == "pause")
		{
			if (Mix_PausedMusic() == 0)
			{
				Mix_PauseMusic();
				(*it)->setActive(false);
			}
		}
		else if ((*it)->getActive() == true && (*it)->getMode() == "resume")
		{
			if (Mix_PausedMusic() == 1)
			{
				Mix_ResumeMusic();
				(*it)->setActive(false);
			}
		}
	}
}

int SoundSystem::GetSoundVolume()
{
	return m_soundVolume;
}

void SoundSystem::SetSoundVolume(int volume)
{
	m_soundVolume = volume;
	for (std::vector<SoundComponent*>::iterator it = sounds.begin(); it != sounds.end(); ++it)
	{
		std::cout << "Volume : " + std::to_string(m_soundVolume) << std::endl;
		(*it)->setVolumeSetter(true);
	}
}

int SoundSystem::GetMusicVolume()
{
	return m_musicVolume;
}

void SoundSystem::SetMusicVolume(int volume)
{
	m_musicVolume = volume;
	for (std::vector<MusicComponent*>::iterator it = music.begin(); it != music.end(); ++it)
	{
		std::cout << "Volume : " + std::to_string(m_musicVolume) << std::endl;
		(*it)->setVolumeSetter(true);
	}
}




