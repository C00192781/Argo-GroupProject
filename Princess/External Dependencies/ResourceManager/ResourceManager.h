#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H

#include <SDL.h>
#include <SDL_audio.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "JSONReader.h"


//Project: Resource Manager.
//By J.Quinn
//Description:: Loads resources, safely disposes of resources, manages recsources and checks for any file changes and applys them to the current resources.
//Safe, efficient, fast.
//Requirements: SimpleJSON


class ResourceManager
{
public:
	ResourceManager(SDL_Renderer* r, std::string dir)
	{
		m_directory = dir;
		m_renderer = r;
		TTF_Init();
	};
	~ResourceManager() {};

	void Update();

	//Texture Stuff
	void AddTexture(std::string id, std::string location);
	void RemoveTexture(std::string id);
	SDL_Texture * GetTexture(std::string id);

	//Font Stuff
	void AddFont(std::string id, std::string location, int size);
	void RemoveFont(std::string id);
	TTF_Font * GetFont(std::string id);

	//Music Stuff
	void AddMusic(std::string id, std::string location);
	void RemoveMusic(std::string id);
	Mix_Music * GetMusic(std::string id);

	//Sound Stuff
	void AddSound(std::string id, std::string location);
	void RemoveSound(std::string id);
	Mix_Chunk * GetSound(std::string id);

	//Map Stuff
	void AddMap(std::string id, std::string location);
	void RemoveMap(std::string id);
	std::string GetMapElement(std::string id, int x, int y);

	//Config Stuff
	void AddConfig(std::string id, std::string location);
	void AddConfigElement(std::string id, std::string configElementId, std::string configElementLoc);
	void RemoveConfig(std::string id);
	std::string GetConfigElement(std::string id, std::string elementID);

private:

	SDL_Renderer * m_renderer;
	std::string m_directory;

	//Textures
	std::vector<SDL_Surface*> m_surfaces;
	std::vector<SDL_Texture*> m_textures;
	std::vector<std::string> m_textureKey;
	std::vector<std::string> m_texturePath;
	std::vector<int> m_textureSize;

	//Music
	std::vector<Mix_Music*> m_music;
	std::vector<std::string> m_musicKey;
	std::vector<std::string> m_musicPath;
	std::vector<int> m_musicSize;

	//Sound
	std::vector<Mix_Chunk*> m_sound;
	std::vector<std::string> m_soundKey;
	std::vector<std::string> m_soundPath;
	std::vector<int> m_soundSize;

	//Font
	std::vector<TTF_Font*> m_fonts;
	std::vector<int> m_fontSizeS;
	std::vector<std::string> m_fontKey;
	std::vector<std::string> m_fontPath;
	std::vector<int> m_fontSize;

	//Map
	std::vector<std::vector<std::vector<std::string>>> m_map;
	std::vector<std::string> m_mapKey;
	std::vector<std::string> m_mapPath;
	std::vector<int> m_mapSize;

	//Config
	std::vector<std::vector<std::string>> m_config;
	std::vector<std::vector<std::string>> m_configElementKeys;
	std::vector<std::vector<std::string>> m_configElementPaths;
	std::vector<std::string> m_configKey;
	std::vector<std::string> m_configPath;
	std::vector<int> m_configSize;

	std::ifstream::pos_type GetFileSize(const char* filename)
	{
		std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
		return in.tellg();
	}
};
#endif
