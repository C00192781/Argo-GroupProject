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
			m_spriteComponent.at(i)->Frame(m_spriteComponent.at(i)->Frame() + 1);
		}
		m_timer = 25;
	}
	else
	{
		m_timer--;
	}
	if (m_cameraOn)
	{
		for (int i = m_entities.size() - 1; i > 0; i--)
		{
			if (m_entities.at(i)->ID() == "Player" && m_entities.at(i)->Control())
			{
				offsetX = m_positionComponent.at(i)->getX();
				offsetY = m_positionComponent.at(i)->getY();
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
			if (m_spriteComponent.at(i)->Layer() == 0)
			{
				backgroundHolder.push_back(i);
			}
			else if (m_spriteComponent.at(i)->Layer() == 1)
			{
				midgroundHolder.push_back(i);
			}
			else if (m_spriteComponent.at(i)->Layer() == 2)
			{
				foregroundHolder.push_back(i);
			}
			else if (m_spriteComponent.at(i)->Layer() == 3)
			{
				finalgroundHolder.push_back(i);
			}
			else
			{
				hudHolder.push_back(i);
			}
		}

		holder.reserve(backgroundHolder.size() + foregroundHolder.size() + hudHolder.size());
		holder.insert(holder.end(), backgroundHolder.begin(), backgroundHolder.end());
		holder.insert(holder.end(), midgroundHolder.begin(), midgroundHolder.end());
		holder.insert(holder.end(), foregroundHolder.begin(), foregroundHolder.end());
		holder.insert(holder.end(), finalgroundHolder.begin(), finalgroundHolder.end());
		holder.insert(holder.end(), hudHolder.begin(), hudHolder.end());
		std::vector<Entity*> entHolder;
		m_positionComponent.clear();
		m_spriteComponent.clear();
		for (int i = 0; i < holder.size(); i++)
		{
			entHolder.push_back(m_entities.at(holder.at(i)));
			int pcKey = -1;
			int scKey = -1;
			for (int j = 0; j < m_entities.at(holder.at(i))->GetComponents()->size(); j++)
			{
				if (m_entities.at(holder.at(i))->GetComponents()->at(j)->Type() == "PC")
				{
					pcKey = j;
				}
				else if (m_entities.at(holder.at(i))->GetComponents()->at(j)->Type() == "SC")
				{
					scKey = j;
				}
				if (scKey > 0 && pcKey > 0)
				{
					break;
				}
			}
			m_positionComponent.push_back(static_cast<PositionComponent*>(m_entities.at(holder.at(i))->GetComponents()->at(pcKey)));
			m_spriteComponent.push_back(static_cast<SpriteComponent*>(m_entities.at(holder.at(i))->GetComponents()->at(scKey)));
		}

		m_sizeMemory = entHolder.size();

		m_entities.clear();
		m_entities = entHolder;
	}
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->Active())
		{
			SDL_Rect holderRect{
				m_positionComponent.at(i)->getX(),
				m_positionComponent.at(i)->getY(),
				m_spriteComponent.at(i)->Width() * (int)m_scale,
				m_spriteComponent.at(i)->Height() * (int)m_scale };
			if (m_spriteComponent.at(i)->Relative())
			{
				SDL_RenderCopy(m_renderer, m_resourceManager->GetTexture(m_spriteComponent.at(i)->Sheet()), &m_spriteComponent.at(i)->GetRect(), &holderRect);
			}
			else
			{
				if (m_cameraOn)
				{
					holderRect.x = (holderRect.x - offsetX) + m_camera.x / 2;
					holderRect.y = (holderRect.y - offsetY) + m_camera.y / 2;
				}
				if (holderRect.x >= -(m_camera.x * 0.1) && holderRect.x <= m_camera.x && holderRect.y > -(m_camera.y * 0.1) && holderRect.y < m_camera.y)
				{
					SDL_RenderCopy(m_renderer, m_resourceManager->GetTexture(m_spriteComponent.at(i)->Sheet()), &m_spriteComponent.at(i)->GetRect(), &holderRect);
				}
			}
		}
	}
}


void RenderSystem::LoadComponent()
{
	int pcKey = -1;
	int scKey = -1;
	for (int j = 0; j < m_entities.back()->GetComponents()->size(); j++)
	{
		if (m_entities.back()->GetComponents()->at(j)->Type() == "PC")
		{
			pcKey = j;
		}
		else if (m_entities.back()->GetComponents()->at(j)->Type() == "SC")
		{
			scKey = j;
		}
		if (scKey > 0 && pcKey > 0)
		{
			break;
		}
	}
	m_positionComponent.push_back(static_cast<PositionComponent*>(m_entities.back()->GetComponents()->at(pcKey)));
	m_spriteComponent.push_back(static_cast<SpriteComponent*>(m_entities.back()->GetComponents()->at(scKey)));
}

void RenderSystem::UnloadComponent(int x)
{
	m_positionComponent.erase(m_positionComponent.begin() + x);
	m_spriteComponent.erase(m_spriteComponent.begin() + x);
	m_positionComponent.shrink_to_fit();
	m_spriteComponent.shrink_to_fit();
}