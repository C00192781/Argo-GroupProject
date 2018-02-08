#include "AISystem.h"
#include <time.h>

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
	SDL_Point p{ 300,0 };
	
	characterFactory = new Princess();
	m_entities.push_back(characterFactory->CharA("Red", p, 0));

	//p =  SDL_Point{ 10,100 };

	characterFactory = new BasicEnemy();
	m_entities.push_back(characterFactory->CharC("Demon", p, 0));

	time_t t;

	srand((unsigned)time(&t));

	//int temp = m_time * 1000;

	int mod1 = rand() % 800;

	int mod2 = rand() % 750;
	
	for (int i = 0; i < 50; i++)
	{
		p.x = rand() % 800;
		p.y = rand()% 760;
	
	//	characterFactory = new BasicEnemy();
		m_entities.push_back(characterFactory->CharC("Demon", p, 0));
	
	}

}


void AiSystem::Spawn(std::string id)
{
	if (id == "1")
	{
		//spawn map 1
	}
	else if (id == "2")
	{
		//spawn map 2
	}
	
}

std::vector<Entity*> AiSystem::getEntities()
{
	return m_entities;
}


void AiSystem::seek(int entityIndex, int pcKey, int mcKey, int seekKey, int acKey)
{
	float x = static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->getXDestination() - static_cast<PositionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(pcKey))->getPosition().x;
	float y = static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->getYDestination() - static_cast<PositionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(pcKey))->getPosition().y;

	float dist = magnitude(x, y);

	static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->setDistanceToDestination(dist);

	if (dist > static_cast<AttributesComponent*>(m_entities.at(entityIndex)->GetComponents()->at(acKey))->MovementSpeed() / 60)
	{
		normalise(x, y);
		x *= static_cast<AttributesComponent*>(m_entities.at(entityIndex)->GetComponents()->at(acKey))->MovementSpeed();
		y *= static_cast<AttributesComponent*>(m_entities.at(entityIndex)->GetComponents()->at(acKey))->MovementSpeed();

		static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setXVelocity(x);
		static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setYVelocity(y);
	}
	else
	{
		static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setXVelocity(0);
		static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setYVelocity(0);
	}
}


void AiSystem::Update()
{
	
}


void AiSystem::Wander(int entityIndex, int pcKey, int mcKey, int seekKey, int acKey)
{
	time_t t;

	srand((unsigned)time(&t));

	int temp = m_time * 1000;

	int mod1 = rand() % 100;

	int mod2 = rand() % 80;

	if (temp % 22 == 0 || temp % 23 == 0)
	{


	//	srand((unsigned)time(&t));


		if (mod1 % 2 == 0)
		{
			static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->setXDestination(400 + mod1);
		}
		else
		{
			static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->setXDestination(400 - mod1);
		}

		if (mod2 % 2 == 0)
		{
			static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->setYDestination(300 + mod2);
		}
		else
		{
			static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->setYDestination(300 - mod2);
		}
		//srand((unsigned)time(&t));
	

		//std::cout << "ROLLING  " << std::endl;
		//std::cout << "ROLLING  " << std::endl;

		//std::cout << "ROLLING  " << std::endl;

		//std::cout << "ROLLING  " << std::endl;
		//std::cout << "ROLLING  " << std::endl;
		//std::cout << "ROLLING  " << std::endl;
		//std::cout << "ROLLING  " << std::endl;
		//std::cout << "ROLLING  " << std::endl;
		//std::cout << "ROLLING  " << std::endl;


	}


	//std::cout << "X: " << static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->getXDestination() << "  Y: " << static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->getYDestination() << std::endl;


	float x = static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->getXDestination() - static_cast<PositionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(pcKey))->getPosition().x;
	float y = static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->getYDestination() - static_cast<PositionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(pcKey))->getPosition().y;

	float dist = magnitude(x, y);

	static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->setDistanceToDestination(dist);

	//if (dist > static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->getSpeed() )
	//{
		normalise(x, y);
		x *= static_cast<AttributesComponent*>(m_entities.at(entityIndex)->GetComponents()->at(acKey))->MovementSpeed();
		y *= static_cast<AttributesComponent*>(m_entities.at(entityIndex)->GetComponents()->at(acKey))->MovementSpeed();

		static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setXVelocity(x);
		static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setYVelocity(y);
	//}
	//else
	//{
	//	static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setXVelocity(0);
	//	static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setYVelocity(0);
	//}


}


void AiSystem::attack(int entityIndex, int attackKey, int mcKey)
{
	static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setXVelocity(0);
	static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setYVelocity(0);
}

void AiSystem::normalise(float &x, float &y)
{
	float mag = magnitude(x, y);

	if (mag > 0)
	{
		x /= mag;
		y /= mag;
	}
}

float AiSystem::magnitude(float x, float y)
{
	//return sqrt(((v2.x - v1.x) * (v2.x - v1.x)) + ((v2.y - v1.y) * (v2.y - v1.y)));
	return sqrt((x * x) + (y * y));
}

void AiSystem::Update(float deltaTime)
{
	m_time = deltaTime;

	//for (int i = 0; i < m_entities.size(); i++)
	//{
	//	int pcKey = -1;
	//	int ailKey = -1;
	//	for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
	//	{
	//		if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC") //position comp
	//		{
	//			pcKey = j;
	//		}
	//		else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "AIL") //ai logic comp
	//		{
	//			ailKey = j;
	//		}
	//	}
	//	if (pcKey >= 0 && ailKey >= 0)
	//	{
	//		if (m_entities.at(i)->ID() == "Princess")
	//		{
	//			//if it's a princess, do something special
	//		}

	//		static_cast<AiLogicComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Speed(1); //set speed

	//		SDL_Point holder{ static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition().x, static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition().y };
	//		//update position with speed
	//		holder.x += static_cast<AiLogicComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Speed();
	//		holder.y += static_cast<AiLogicComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Speed();

	//		static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->setPosition(holder);

	//	}
	//}

	for (int i = 0; i < m_entities.size(); i++)
	{
		int pcKey = -1;
		int mcKey = -1;
		int seekKey = -1;
		int attackKey = -1;
		int acKey = -1;

		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC")
			{
				pcKey = j;
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "movement")
			{
				mcKey = j;
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "seek")
			{
				seekKey = j;
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "attack")
			{
				attackKey = j;
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "AC")
			{
				acKey = j;
			}
		}


		if (seekKey >= 0 && pcKey >= 0 && mcKey >= 0 && acKey >= 0)
		{
			if (attackKey >= 0)
			{
				if (static_cast<SeekComponent*>(m_entities.at(i)->GetComponents()->at(seekKey))->getDistanceToDestination() < static_cast<AttackComponent*>(m_entities.at(i)->GetComponents()->at(attackKey))->getRange())
				{
					attack(i, attackKey, mcKey);
				}
				else
				{
					seek(i, pcKey, mcKey, seekKey,acKey);
				}
			}
			else
			{
				seek(i, pcKey, mcKey, seekKey,acKey);
			}

			if (m_entities.at(i)->ID() == "Princess")
			{
				Wander(i, pcKey, mcKey, seekKey,acKey);


				//m_entities.at(i)->RemoveComponent(new MovementComponent*);
				//
				//SDL_Point holder = SDL_Point{100 , 100};
				//
				//static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->setPosition(holder);

				//Wander(i, pcKey, mcKey, seekKey);
				//do Princess things
			}

			else if (m_entities.at(i)->ID() == "Melee Enemy")
			{
				//do melee enemy things
			}

			else if (m_entities.at(i)->ID() == "Ranged Enemy")
			{
				//do ranged enemy things
			}

			else if (m_entities.at(i)->ID() == "Spellcaster Enemy")
			{
				//do Spellcaster enemy things
			}

			else if (m_entities.at(i)->ID() == "Basic Enemy")
			{
				//do basic enemy things
			}
		}
	

		

	}

}