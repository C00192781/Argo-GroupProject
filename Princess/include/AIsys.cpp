#include "AiSys.h"



AiSystem::AiSystem()
{
	m_thingy = 1;
}


AiSystem::~AiSystem()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities.at(i);
		m_entities.erase(m_entities.begin() + i);
		m_entities.shrink_to_fit();
	}
}

void AiSystem::Update()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		int pcKey = -1;
		int ailKey = -1;
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC")
			{
				pcKey = j;
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "AIL")
			{
				ailKey = j;
			}
		}
		if (pcKey >= 0 && ailKey >= 0)
		{
			if (m_entities.at(i)->ID() == "Princess")
			{
				auto temp = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->X();
				int donothing = 0;
				donothing -= 1;
			}

			auto temp1 = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->X();
			auto temp2 = static_cast<AiLogicComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Speed();

			static_cast<AiLogicComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Money(1);

			auto temp3 = static_cast<AiLogicComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Money();




			SDL_Point holder{ static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->X(), static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Y() };

			holder.x += static_cast<AiLogicComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Money();
			holder.y += static_cast<AiLogicComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Money();


			static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->X(holder.x);
			static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Y(holder.y);

			//SDL_Rect* holder = new SDL_Rect{ static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->X(), static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Y(), static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(ailKey))->Width() * m_scale, static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(ailKey))->Height()*m_scale };
			//SDL_RenderCopy(m_renderer,
			//	m_resourceManager->GetTexture(static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(ailKey))->Sheet()),
			//	&static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(ailKey))->GetRect(), holder);
			//delete holder;
		}
	}
}
