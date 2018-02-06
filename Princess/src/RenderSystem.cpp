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
	std::vector<int> backgroundHolder;
	std::vector<int> foregroundHolder;
	std::vector<int> hudHolder;
	std::vector<int> holder;
	if (m_timer <= 0)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "SC")
				{
					static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(j))->Frame(static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(j))->Frame() + 1);
				}
			}
		}
		m_timer = 60;
	}
	else
	{
		m_timer--;
	}
	for (int i = 0; i < m_entities.size(); i++)
	{
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "SC")
			{
				if (static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(j))->Layer() == 0)
				{
					backgroundHolder.push_back(i);
				}
				else if (static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(j))->Layer() == 1)
				{
					foregroundHolder.push_back(i);
				}
				else if (static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(j))->Layer() == 2)
				{
					hudHolder.push_back(i);
				}
			}
		}
	}

	holder.reserve(backgroundHolder.size() + foregroundHolder.size() + hudHolder.size());
	holder.insert(holder.end(), backgroundHolder.begin(), backgroundHolder.end());
	holder.insert(holder.end(), foregroundHolder.begin(), foregroundHolder.end());
	holder.insert(holder.end(), hudHolder.begin(), hudHolder.end());

	for (int i = 0; i < holder.size(); i++)
	{
		int rectangleKey = -1;
		int scKey = -1;
		for (int j = 0; j < m_entities.at(holder.at(i))->GetComponents()->size(); j++)
		{
			if (m_entities.at(holder.at(i))->GetComponents()->at(j)->Type() == "rectangle")
			{
				rectangleKey = j;
			}
			else if (m_entities.at(holder.at(i))->GetComponents()->at(j)->Type() == "SC")
			{
				scKey = j;
			}
		}
		if (rectangleKey >= 0 && scKey >= 0)
		{
			SDL_Rect* holderRect = new SDL_Rect{ 
				static_cast<RectangleComponent*>(m_entities.at(holder.at(i))->GetComponents()->at(rectangleKey))->getPosition().x, 
				static_cast<RectangleComponent*>(m_entities.at(holder.at(i))->GetComponents()->at(rectangleKey))->getPosition().y, 
				static_cast<SpriteComponent*>(m_entities.at(holder.at(i))->GetComponents()->at(scKey))->Width() * (int)m_scale, 
				static_cast<SpriteComponent*>(m_entities.at(holder.at(i))->GetComponents()->at(scKey))->Height() * (int)m_scale };
			SDL_RenderCopy(m_renderer, m_resourceManager->GetTexture(static_cast<SpriteComponent*>(m_entities.at(holder.at(i))->GetComponents()->at(scKey))->Sheet()), &static_cast<SpriteComponent*>(m_entities.at(holder.at(i))->GetComponents()->at(scKey))->GetRect(), holderRect);
			delete holderRect;
		}
	}
}
