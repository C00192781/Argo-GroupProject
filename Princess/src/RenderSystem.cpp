#include "RenderSystem.h"



RenderSystem::RenderSystem(ResourceManager * rm, SDL_Renderer * r)
{
	m_renderer = r;
	m_resourceManager = rm;
	m_scale = 1;
}


RenderSystem::~RenderSystem()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities.at(i);
		m_entities.erase(m_entities.begin() + i);
		m_entities.shrink_to_fit();
	}
}

void RenderSystem::Update()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		int pcKey = -1;
		int scKey = -1;
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC")
			{
				pcKey = j;
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "SC")
			{
				scKey = j;
			}
		}
		if (pcKey >= 0 && scKey >= 0)
		{
			//std::cout << static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition().x << std::endl;

			SDL_Rect* holder = new SDL_Rect{ static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition().x, static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition().y, static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(scKey))->Width() * m_scale, static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(scKey))->Height()*m_scale };
			SDL_RenderCopy(m_renderer, 
							m_resourceManager->GetTexture(static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(scKey))->Sheet()), 
							&static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(scKey))->GetRect(), holder);
			delete holder;
		}
	}
}
