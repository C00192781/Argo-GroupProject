#ifndef _RENDERSYSTEM_H
#define _RENDERSYSTEM_H

#include "System.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
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
};
#endif
