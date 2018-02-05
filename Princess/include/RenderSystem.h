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
	void SetScale(float x) { m_scale = x; };
	float GetScale() { return m_scale; };
private:
	SDL_Renderer * m_renderer;
	ResourceManager * m_resourceManager;
	float m_scale;
	//int m_scale;
	int m_timer;
};
#endif
