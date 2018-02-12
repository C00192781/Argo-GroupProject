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
	void Draw();
	void SetScale(float x) { m_scale = x; };
	float GetScale() { return m_scale; };

	void Camera(bool x) { m_cameraOn = x; }
	void Camera(int width, int height) { m_camera.x = width; m_camera.y = height; };

private:
	void LoadComponent();
	void UnloadComponent(int x);
	SDL_Renderer * m_renderer;
	ResourceManager * m_resourceManager;
	int m_scale;
	int m_timer;
	int m_sizeMemory;
	bool m_cameraOn;
	SDL_Point m_camera;

	std::vector<PositionComponent*> m_positionComponent;
	std::vector<SpriteComponent*> m_spriteComponent;
};
#endif