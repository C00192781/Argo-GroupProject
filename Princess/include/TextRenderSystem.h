#ifndef _TEXTRENDERCOMPONENT_H
#define _TEXTRENDERCOMPONENT_H

#include "System.h"
#include "TextComponent.h"
#include "PositionComponent.h"
#include "ResourceManager.h"
class TextRenderSystem : public System
{
public:
	TextRenderSystem(ResourceManager * r, SDL_Renderer * re);
	~TextRenderSystem();

	void Update();

private:

		void LoadComponent();
		void UnloadComponent(int x);
		std::vector<PositionComponent*> m_positionComponents;
		std::vector<TextComponent*> m_textComponents;

		float m_scale;

		ResourceManager* m_resources;
		SDL_Renderer* m_renderer;

};
#endif

