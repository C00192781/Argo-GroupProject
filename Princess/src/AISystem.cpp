#include "AISystem.h"


AiSystem::AiSystem()
{
	//m_thingy = 1;
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


void AiSystem::Spawn()
{
	/*m_entities.clear();
	m_entities.push_back(m_entities);*/
	//TileFactory * m_factory;
	//m_entities.push_back(new Character)

	SDL_Point p{ 0,0 };

	characterFactory = new Princess();
	m_entities.push_back(characterFactory->CharA("Red", p, 0));

	//m_entities.push_back(CharFactory);
}


void AiSystem::Spawn(std::vector<Entity*> entities)
{
	/*m_entities.clear();
	m_entities.push_back(m_entities);*/
	//TileFactory * m_factory;

	//m_entities.push_back(new Princess());
	//
	//CharFactory.push_back(new Princess());

	
}

std::vector<Entity*> AiSystem::getEntities()
{
	return m_entities;
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
				auto temp = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition().x;
				int donothing = 0;
				donothing -= 1;
			}


		//	std::cout << "x: " << static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition().x << std::endl;

			static_cast<AiLogicComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Money(1);

		//	auto tempy = static_cast<AiLogicComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Speed();

		//	auto temp3 = static_cast<AiLogicComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Money();





			SDL_Point holder{ static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition().x, static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition().y };

			holder.x += static_cast<AiLogicComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Money();
			holder.y += static_cast<AiLogicComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Money();

			static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->setPosition(holder);

		//	std::cout << "x: " << static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition().x << std::endl;




		//	static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->setPosition(holder);

			//SDL_Rect* holder = new SDL_Rect{ static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->X(), static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Y(), static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(ailKey))->Width() * m_scale, static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(ailKey))->Height()*m_scale };
			//SDL_RenderCopy(m_renderer,
			//	m_resourceManager->GetTexture(static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(ailKey))->Sheet()),
			//	&static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(ailKey))->GetRect(), holder);
			//delete holder;
		}
	}
}