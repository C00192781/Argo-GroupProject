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
	int offsetX = 0;
	int offsetY = 0;
	if (m_timer <= 0)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "SC")
				{
					static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(j))->Frame(static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(j))->Frame() + 1);
					break;
				}
			}
		}
		m_timer = 25;
	}
	else
	{
		m_timer--;
	}
	bool finish = false;
	if (m_cameraOn)
	{
		for (int i = m_entities.size() - 1; i > 0; i--)
		{
			if (m_entities.at(i)->ID() == "Player")
			{
				for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
				{
					if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC")
					{
						offsetX = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(j))->getPosition().x;
						offsetY = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(j))->getPosition().y;
						finish = true;
						break;
					}
				}
			}
			if (finish)
			{
				break;
			}
		}
	}
	if (m_sizeMemory != m_entities.size())
	{
		std::vector<int> backgroundHolder;
		std::vector<int> midgroundHolder;
		std::vector<int> foregroundHolder;
		std::vector<int> finalgroundHolder;
		std::vector<int> hudHolder;
		std::vector<int> holder;
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
						midgroundHolder.push_back(i);
					}
					else if (static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(j))->Layer() == 2)
					{
						foregroundHolder.push_back(i);
					}
					else if (static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(j))->Layer() == 3)
					{
						finalgroundHolder.push_back(i);
					}
					else
					{
						hudHolder.push_back(i);
					}
				}
			}
		}

		holder.reserve(backgroundHolder.size() + foregroundHolder.size() + hudHolder.size());
		holder.insert(holder.end(), backgroundHolder.begin(), backgroundHolder.end());
		holder.insert(holder.end(), midgroundHolder.begin(), midgroundHolder.end());
		holder.insert(holder.end(), foregroundHolder.begin(), foregroundHolder.end());
		holder.insert(holder.end(), finalgroundHolder.begin(), finalgroundHolder.end());
		holder.insert(holder.end(), hudHolder.begin(), hudHolder.end());

		std::vector<Entity*> entHolder;
		for (int i = 0; i < holder.size(); i++)
		{
			entHolder.push_back(m_entities.at(holder.at(i)));
		}

		m_sizeMemory = entHolder.size();

		m_entities.clear();
		m_entities = entHolder;
	}

	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->Active())
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
				else if (scKey > 0 && pcKey > 0)
				{
					break;
				}
			}
			if (pcKey >= 0 && scKey >= 0)
			{
				SDL_Rect holderRect{
					static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition().x,
					static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition().y,
					static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(scKey))->Width() * (int)m_scale,
					static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(scKey))->Height() * (int)m_scale };
				if (m_cameraOn)
				{
					holderRect.x = (holderRect.x - offsetX) + m_camera.x / 2;
					holderRect.y = (holderRect.y - offsetY) + m_camera.y / 2;
				}
				if (holderRect.x >= -(m_camera.x * 0.1) && holderRect.x <= m_camera.x && holderRect.y > -(m_camera.y * 0.1) && holderRect.y < m_camera.y)
				{
					SDL_RenderCopy(m_renderer, m_resourceManager->GetTexture(static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(scKey))->Sheet()), &static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(scKey))->GetRect(), &holderRect);
				}
			}
		}
	}
}
