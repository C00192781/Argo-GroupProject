#include "TextRenderSystem.h"



TextRenderSystem::TextRenderSystem(ResourceManager * r, SDL_Renderer * re)
{
	m_entities.push_back(new Entity("Null"));
	delete m_entities.back();
	m_entities.clear();
	m_resources = r;
	m_renderer = re;
}

TextRenderSystem::~TextRenderSystem()
{
}

void TextRenderSystem::Update()
{
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Rect rect;

	for (int i = 0; i < m_entities.size(); i++)
	{
		surface = TTF_RenderText_Blended_Wrapped(m_resources->GetFont(m_textComponents.at(i)->FontID()), m_textComponents.at(i)->Text().c_str(), m_textComponents.at(i)->Color(), m_textComponents.at(i)->Width());
		texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		rect = SDL_Rect{ (int)m_positionComponents.at(i)->getX() + 8, (int)m_positionComponents.at(i)->getY() + 8,  surface->w, surface->h};

		SDL_RenderCopy(m_renderer, texture, NULL, &rect);

		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surface);
	}
}

void TextRenderSystem::LoadComponent()
{
	int pcKey = -1;
	int tcKey = -1;
	for (int j = 0; j < m_entities.back()->GetComponents()->size(); j++)
	{
		if (m_entities.back()->GetComponents()->at(j)->Type() == "PC")
		{
			pcKey = j;
		}
		else if (m_entities.back()->GetComponents()->at(j)->Type() == "TextComponent")
		{
			tcKey = j;
		}
		if (tcKey > 0 && pcKey > 0)
		{
			break;
		}
	}
	m_positionComponents.push_back(static_cast<PositionComponent*>(m_entities.back()->GetComponents()->at(pcKey)));
	m_textComponents.push_back(static_cast<TextComponent*>(m_entities.back()->GetComponents()->at(tcKey)));
}
void TextRenderSystem::UnloadComponent(int x)
{
	m_positionComponents.erase(m_positionComponents.begin() + x);
	m_textComponents.erase(m_textComponents.begin() + x);
	m_positionComponents.shrink_to_fit();
	m_textComponents.shrink_to_fit();
}