#ifndef _RENDERSYSTEM_H
#define _RENDERSYSTEM_H

#include "System.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include <iostream>

class RenderSystem : public System
{
public:
	RenderSystem(ResourceManager * rm, SDL_Renderer * r);
	~RenderSystem();
	void Update();
	void SetScale(int x) { m_scale = x; };
private:
	SDL_Renderer * m_renderer;
	ResourceManager * m_resourceManager;
	int m_scale;

	int x = 200;
	int y = 200; 
	float velocityX, velocityY = 0; 
	float conversion = 180 / 3.14159265359;
	float orientation = 0;
	float tempX, tempY = 0;
};
#endif
