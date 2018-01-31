#include "ResourceManager.h"

//Used to detect underlying file changes.
void ResourceManager::Update()
{
	for (int i = 0; i < m_textureKey.size(); i++)
	{
		std::string holder = m_directory + "/Texture/" + m_texturePath.at(i);
		if (m_textureSize.at(i) != GetFileSize(holder.c_str()))
		{
			std::string holderPath = m_texturePath.at(i);
			std::string holderKey = m_textureKey.at(i);
			RemoveTexture(m_textureKey.at(i));
			AddTexture(holderKey, holderPath);
		}
	}
	for (int i = 0; i < m_fontKey.size(); i++)
	{
		std::string holder = m_directory + "/Font/" + m_fontPath.at(i);
		if (m_fontSize.at(i) != GetFileSize(holder.c_str()))
		{
			std::string holderPath = m_fontPath.at(i);
			std::string holderKey = m_fontKey.at(i);
			int sizeHolder = m_fontSizeS.at(i);
			RemoveFont(m_fontKey.at(i));
			AddFont(holderKey, holderPath, sizeHolder);
		}
	}
	for (int i = 0; i < m_musicKey.size(); i++)
	{
		std::string holder = m_directory + "/Music/" + m_musicPath.at(i);
		if (m_musicSize.at(i) != GetFileSize(holder.c_str()))
		{
			std::string holderPath = m_musicPath.at(i);
			std::string holderKey = m_musicKey.at(i);
			RemoveMusic(m_musicKey.at(i));
			AddMusic(holderKey, holderPath);
		}
	}
	for (int i = 0; i < m_soundKey.size(); i++)
	{
		std::string holder = m_directory + "/Sound/" + m_soundPath.at(i);
		if (m_soundSize.at(i) != GetFileSize(holder.c_str()))
		{
			std::string holderPath = m_soundPath.at(i);
			std::string holderKey = m_soundKey.at(i);
			RemoveSound(m_soundKey.at(i));
			AddSound(holderKey, holderPath);
		}
	}
	for (int i = 0; i < m_mapKey.size(); i++)
	{
		std::string holder = m_directory + "/Map/" + m_mapPath.at(i);
		if (m_mapSize.at(i) != GetFileSize(holder.c_str()))
		{
			std::string holderPath = m_mapPath.at(i);
			std::string holderKey = m_mapKey.at(i);
			RemoveMap(m_mapKey.at(i));
			AddMap(holderKey, holderPath);
		}
	}
	for (int i = 0; i < m_configKey.size(); i++)
	{
		std::string holder = m_directory + "/Config/" + m_configPath.at(i);
		if (m_configSize.at(i) != GetFileSize(holder.c_str()))
		{
			std::string holderPath = m_configPath.at(i);
			std::string holderKey = m_configKey.at(i);
			std::vector<std::string> holderElementPath = m_configElementPaths.at(i);
			std::vector<std::string> holderElementKey = m_configElementKeys.at(i);
			RemoveConfig(m_configKey.at(i));
			AddConfig(holderKey, holderPath);
			for (int j = 0; j < holderElementKey.size(); j++)
			{
				AddConfigElement(holderKey, holderElementKey.at(j), holderElementPath.at(j));
			}
		}
	}
}

//Texture Stuff - Checks to see if file exists and/or if the file exists. If so, appends it to a vector.
void ResourceManager::AddTexture(std::string id, std::string location)
{
	std::string holder = m_directory + "/Texture/" + location;
	SDL_Surface * temp;
	const char * tempLocation = holder.c_str();
	if (!(temp = IMG_Load(tempLocation)))
	{
		std::cout << "Could not load " << id << "! Loading Placeholder!" << std::endl;
		temp = IMG_Load((m_directory + "/Texture/placeholder.png").c_str());
		m_textureSize.push_back(GetFileSize((m_directory + "/Texture/placeholder.png").c_str()));
		m_surfaces.push_back(temp);
		SDL_Texture * tempTexture = SDL_CreateTextureFromSurface(m_renderer, m_surfaces.back());
		m_textures.push_back(tempTexture);
		m_textureKey.push_back(id);
		m_texturePath.push_back("placeholder.png");
	}
	else
	{
		for (int i = 0; i < m_texturePath.size(); i++)
		{
			if (m_texturePath.at(i) == holder)
			{
				return;
			}
		}
		m_texturePath.push_back(location);
		std::cout << "Loaded " << id << "!" << std::endl;
		m_surfaces.push_back(temp);
		SDL_Texture * tempTexture = SDL_CreateTextureFromSurface(m_renderer, m_surfaces.back());
		m_textures.push_back(tempTexture);
		m_textureKey.push_back(id);
		m_textureSize.push_back(GetFileSize(tempLocation));
	}
}
//Removes texture, if it's on the vector.
void ResourceManager::RemoveTexture(std::string id)
{
	int holder = -1;
	for (int i = 0; i < m_textureKey.size(); i++)
	{
		if (m_textureKey.at(i) == id)
		{
			holder = i;
			break;
		}
	}
	if (holder != -1)
	{
		m_textureKey.erase(m_textureKey.begin() + holder);
		m_textureKey.shrink_to_fit();

		SDL_DestroyTexture(m_textures.at(holder));
		m_textures.erase(m_textures.begin() + holder);
		m_textures.shrink_to_fit();

		SDL_FreeSurface(m_surfaces.at(holder));
		m_surfaces.erase(m_surfaces.begin() + holder);
		m_surfaces.shrink_to_fit();

		m_texturePath.erase(m_texturePath.begin() + holder);
		m_texturePath.shrink_to_fit();

		m_textureSize.erase(m_textureSize.begin() + holder);
		m_textureSize.shrink_to_fit();
	}
	else
	{
		std::cout << "Could not find " << id << "!" << std::endl;
	}
}
//Gets the texture using a key.
SDL_Texture * ResourceManager::GetTexture(std::string id)
{
	for (int i = 0; i < m_textureKey.size(); i++)
	{
		if (m_textureKey.at(i) == id)
		{
			return m_textures.at(i);
		}
	}
	std::cout << "Could not find " << id << "!" << std::endl;
	return 0;
}
//

//Font Stuff
void ResourceManager::AddFont(std::string id, std::string location, int size)
{
	std::string temp = m_directory + "/Font/" + location;
	const char * tempLocation = temp.c_str();
	TTF_Font * holder;
	if (!(holder = TTF_OpenFont(tempLocation, size)))
	{
		m_fontPath.push_back("placeholder.ttf");
		std::cout << "Could not load " << id << "! Loading Placeholder!" << std::endl;
		temp = m_directory + "/Font/placeholder.ttf";
		tempLocation = temp.c_str();
		holder = TTF_OpenFont(tempLocation, size);
		m_fonts.push_back(holder);
		m_fontKey.push_back(id);
		m_fontSize.push_back(GetFileSize(temp.c_str()));

		m_fontSizeS.push_back(size);

	}
	else
	{
		for (int i = 0; i < m_fontPath.size(); i++)
		{
			if (m_fontPath.at(i) == temp)
			{
				return;
			}
		}
		m_fontPath.push_back(location);
		std::cout << "Loaded " << id << "!" << std::endl;
		m_fonts.push_back(holder);
		m_fontKey.push_back(id);
		m_fontSize.push_back(GetFileSize(tempLocation));
		m_fontSizeS.push_back(size);

	}
}
void ResourceManager::RemoveFont(std::string id)
{
	int holder = -1;
	for (int i = 0; i < m_fontKey.size(); i++)
	{
		if (m_fontKey.at(i) == id)
		{
			holder = i;
			break;
		}
	}
	if (holder != -1)
	{
		m_fontKey.erase(m_fontKey.begin() + holder);
		m_fontKey.shrink_to_fit();

		TTF_CloseFont(m_fonts.at(holder));
		m_fonts.erase(m_fonts.begin() + holder);
		m_fonts.shrink_to_fit();

		m_fontPath.erase(m_fontPath.begin() + holder);
		m_fontPath.shrink_to_fit();

		m_fontSize.erase(m_fontSize.begin() + holder);
		m_fontSize.shrink_to_fit();

		m_fontSizeS.erase(m_fontSizeS.begin() + holder);
		m_fontSizeS.shrink_to_fit();
	}
	else
	{
		std::cout << "Could not find " << id << "!" << std::endl;
	}
}

TTF_Font * ResourceManager::GetFont(std::string id)
{
	for (int i = 0; i < m_fontKey.size(); i++)
	{
		if (m_fontKey.at(i) == id)
		{
			return m_fonts.at(i);
		}
	}
	std::cout << "Could not find " << id << "!" << std::endl;
	return 0;
}
//

//Music Stuff
void ResourceManager::AddMusic(std::string id, std::string location)
{
	std::string holder = m_directory + "/Music/" + location;
	Mix_Music * temp;
	const char * tempLocation = holder.c_str();
	if (!(temp = Mix_LoadMUS(tempLocation)))
	{
		std::cout << "Could not load " << id << "! Loading Placeholder!" << std::endl;
		temp = Mix_LoadMUS((m_directory + "/Music/placeholder.wav").c_str());
		m_music.push_back(temp);
		m_musicKey.push_back(id);
		m_musicPath.push_back("placeholder.wav");
		m_musicSize.push_back(GetFileSize((m_directory + "/Music/placeholder.wav").c_str()));
	}
	else
	{
		for (int i = 0; i < m_musicPath.size(); i++)
		{
			if (m_musicPath.at(i) == holder)
			{
				return;
			}
		}
		m_musicPath.push_back(location);
		std::cout << "Loaded " << id << "!" << std::endl;
		m_music.push_back(temp);
		m_musicKey.push_back(id);
		m_musicSize.push_back(GetFileSize(tempLocation));
	}
}
void ResourceManager::RemoveMusic(std::string id)
{
	int holder = -1;
	for (int i = 0; i < m_musicKey.size(); i++)
	{
		if (m_musicKey.at(i) == id)
		{
			holder = i;
			break;
		}
	}
	if (holder != -1)
	{
		m_musicKey.erase(m_musicKey.begin() + holder);
		m_musicKey.shrink_to_fit();
		Mix_FreeMusic(m_music.at(holder));
		m_music.erase(m_music.begin() + holder);
		m_music.shrink_to_fit();
		m_musicPath.erase(m_musicPath.begin() + holder);
		m_musicPath.shrink_to_fit();
		m_musicSize.erase(m_musicSize.begin() + holder);
		m_musicSize.shrink_to_fit();
	}
	else
	{
		std::cout << "Could not find " << id << "!" << std::endl;
	}
}
Mix_Music * ResourceManager::GetMusic(std::string id)
{
	for (int i = 0; i < m_musicKey.size(); i++)
	{
		if (m_musicKey.at(i) == id)
		{
			return m_music.at(i);
		}
	}
	std::cout << "Could not find " << id << "!" << std::endl;
	return 0;
}
//

//Sound Stuff
void ResourceManager::AddSound(std::string id, std::string location)
{
	std::string holder = m_directory + "/Sound/" + location;
	Mix_Chunk * temp;
	const char * tempLocation = holder.c_str();
	if (!(temp = Mix_LoadWAV(tempLocation)))
	{
		std::cout << "Could not load " << id << "! Loading Placeholder!" << std::endl;
		temp = Mix_LoadWAV((m_directory + "/Sound/placeholder.wav").c_str());
		m_sound.push_back(temp);
		m_soundKey.push_back(id);
		m_soundPath.push_back("placeholder.wav");
		m_soundSize.push_back(GetFileSize((m_directory + "/Sound/placeholder.wav").c_str()));
	}
	else
	{
		for (int i = 0; i < m_soundPath.size(); i++)
		{
			if (m_soundPath.at(i) == holder)
			{
				return;
			}
		}
		m_soundPath.push_back(location);
		std::cout << "Loaded " << id << "!" << std::endl;
		m_sound.push_back(temp);
		m_soundKey.push_back(id);
		m_soundSize.push_back(GetFileSize(tempLocation));
	}
}
void ResourceManager::RemoveSound(std::string id)
{
	int holder = -1;
	for (int i = 0; i < m_soundKey.size(); i++)
	{
		if (m_soundKey.at(i) == id)
		{
			holder = i;
			break;
		}
	}
	if (holder != -1)
	{
		m_soundKey.erase(m_soundKey.begin() + holder);
		m_soundKey.shrink_to_fit();
		Mix_FreeChunk(m_sound.at(holder));
		m_sound.erase(m_sound.begin() + holder);
		m_sound.shrink_to_fit();
		m_soundPath.erase(m_soundPath.begin() + holder);
		m_soundPath.shrink_to_fit();
		m_soundSize.erase(m_soundSize.begin() + holder);
		m_soundSize.shrink_to_fit();
	}
	else
	{
		std::cout << "Could not find " << id << "!" << std::endl;
	}
}
Mix_Chunk * ResourceManager::GetSound(std::string id)
{
	for (int i = 0; i < m_soundKey.size(); i++)
	{
		if (m_soundKey.at(i) == id)
		{
			return m_sound.at(i);
		}
	}
	std::cout << "Could not find " << id << "!" << std::endl;
	return 0;
}
//

//Map Stuff
void ResourceManager::AddMap(std::string id, std::string location)
{
	std::string holder = m_directory + "/Map/" + location;
	const char * tempLocation = holder.c_str();
	JSONReader temp = JSONReader(tempLocation);
	if ((temp.load(tempLocation) != 1))
	{
		std::cout << "Could not load " << id << "! Loading Placeholder!" << std::endl;
		temp = JSONReader(m_directory + "/Map/placeholder.json");
		temp.load(m_directory + "/Map/placeholder.json");
		m_map.push_back(temp.loadLevel());
		m_mapKey.push_back(id);
		m_mapPath.push_back("placeholder.json");
		m_mapSize.push_back(GetFileSize((m_directory + "/Map/placeholder.json").c_str()));
	}
	else
	{
		for (int i = 0; i < m_mapPath.size(); i++)
		{
			if (m_mapPath.at(i) == holder)
			{
				return;
			}
		}
		std::cout << "Loaded " << id << "!" << std::endl;
		m_map.push_back(temp.loadLevel());
		m_mapKey.push_back(id);
		m_mapPath.push_back(location);
		m_mapSize.push_back(GetFileSize(tempLocation));
	}
}
void ResourceManager::RemoveMap(std::string id)
{
	int holder = -1;
	for (int i = 0; i < m_mapKey.size(); i++)
	{
		if (m_mapKey.at(i) == id)
		{
			holder = i;
			break;
		}
	}
	if (holder != -1)
	{
		m_mapKey.erase(m_mapKey.begin() + holder);
		m_mapKey.shrink_to_fit();
		m_map.erase(m_map.begin() + holder);
		m_map.shrink_to_fit();
		m_mapPath.erase(m_mapPath.begin() + holder);
		m_mapPath.shrink_to_fit();
		m_mapSize.erase(m_mapSize.begin() + holder);
		m_mapSize.shrink_to_fit();
	}
	else
	{
		std::cout << "Could not find " << id << "!" << std::endl;
	}
}
std::string ResourceManager::GetMapElement(std::string id, int x, int y)
{
	for (int i = 0; i < m_mapKey.size(); i++)
	{
		if (m_mapKey.at(i) == id)
		{
			return m_map.at(i).at(x).at(y);
		}
	}
	std::cout << "Could not find " << id << "!" << std::endl;
	return 0;
}
//

//Config Stuff
void ResourceManager::AddConfig(std::string id, std::string location)
{
	std::string holder = m_directory + "/Config/" + location;
	const char * tempLocation = holder.c_str();
	JSONReader *temp = new JSONReader(tempLocation);
	if ((temp->load(tempLocation) != 1))
	{
		std::cout << "Could not load " << id << "! Loading Placeholder!" << std::endl;
		m_configKey.push_back(id);
		m_configPath.push_back("placeholder.json");
		m_soundSize.push_back(GetFileSize((m_directory + "/config/placeholder.json").c_str()));
	}
	else
	{
		for (int i = 0; i < m_configPath.size(); i++)
		{
			if (m_configPath.at(i) == holder)
			{
				return;
			}
		}
		std::cout << "Loaded " << id << "!" << std::endl;
		m_config.push_back(std::vector<std::string>());
		m_configKey.push_back(id);
		m_configElementKeys.push_back(std::vector<std::string>());
		m_configElementPaths.push_back(std::vector<std::string>());
		m_configPath.push_back(location);
		m_configSize.push_back(GetFileSize(tempLocation));
	}
	delete temp;
}
void ResourceManager::AddConfigElement(std::string id, std::string configElementId, std::string configElementLoc)
{
	int idholder = -1;
	for (int i = 0; i < m_configKey.size(); i++)
	{
		if (m_configKey.at(i) == id)
		{
			idholder = i;
		}
	}
	if (idholder == -1)
	{
		return;
	}
	std::string holder = m_directory + "/Config/" + m_configPath.at(idholder);
	const char * tempLocation = holder.c_str();
	JSONReader *temp = new JSONReader(tempLocation);
	for (int i = 0; i < m_configElementKeys.at(idholder).size(); i++)
	{
		if (m_configElementKeys.at(idholder).at(i) == configElementId)
		{
			return;
		}
	}
	holder = temp->ElementGetter(configElementLoc);
	m_configElementPaths.at(idholder).push_back(configElementLoc);
	m_configElementKeys.at(idholder).push_back(configElementId);
	m_config.at(idholder).push_back(holder);
	delete temp;
}
void ResourceManager::RemoveConfig(std::string id)
{
	int holder = -1;
	for (int i = 0; i < m_configKey.size(); i++)
	{
		if (m_configKey.at(i) == id)
		{
			holder = i;
			break;
		}
	}
	if (holder != -1)
	{
		m_configKey.erase(m_configKey.begin() + holder);
		m_configKey.shrink_to_fit();
		m_configElementKeys.erase(m_configElementKeys.begin() + holder);
		m_configElementKeys.shrink_to_fit();
		m_config.erase(m_config.begin() + holder);
		m_config.shrink_to_fit();
		m_configPath.erase(m_configPath.begin() + holder);
		m_configPath.shrink_to_fit();
		m_configSize.erase(m_configSize.begin() + holder);
		m_configSize.shrink_to_fit();
		m_configElementPaths.erase(m_configElementPaths.begin() + holder);
		m_configElementPaths.shrink_to_fit();
	}
	else
	{
		std::cout << "Could not find " << id << "!" << std::endl;
	}
}
std::string ResourceManager::GetConfigElement(std::string id, std::string elementID)
{
	for (int i = 0; i < m_configKey.size(); i++)
	{
		if (m_configKey.at(i) == id)
		{
			for (int j = 0; j < m_configElementKeys.at(i).size(); j++)
			{
				if (m_configElementKeys.at(i).at(j) == elementID)
				{
					return m_config.at(i).at(j);
				}
			}
		}
	}
	std::cout << "Could not find " << id << "!" << std::endl;
	return 0;
}



