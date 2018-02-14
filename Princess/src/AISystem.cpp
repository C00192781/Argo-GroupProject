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


void AiSystem::LoadComponent()
{

}

void AiSystem::UnloadComponent(int x)
{

}

void AiSystem::Spawn()
{
	//add root node   the very first 'Question' or decision to be made
	//is monster health greater than player health?
	m_decisionTree->CreateRootNode(1);

	//add nodes depending on decisions
	//2nd decision to be made
	//is monster strength greater than player strength?


	//depending on the weights of all three decisions, will return certain node result
	//results!
	//Run, Attack, 

	


	//$$$
	m_decisionTree->AddNode1(m_decisionTree->m_RootNode, 1, 2);
	m_decisionTree->AddNode1(m_decisionTree->m_RootNode, 1, 3);
	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch1, 2, 4);
	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch1, 2, 5);


	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch2, 3,6); //fix addnodes to support larger treesizes soontm.
	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch2, 3, 7);
//	m_decisionTree->printLeafNodes(m_decisionTree->m_RootNode); //this worky workies
	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch1->NewBranch1, 4,8);
	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch1->NewBranch1, 4, 9);


	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch1->NewBranch2, 5, 10);
	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch1->NewBranch2, 5, 11);

	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch2->NewBranch1, 6, 12);
	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch2->NewBranch1, 6, 13);

	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch2->NewBranch2, 7, 14);
	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch2->NewBranch2, 7, 15);



	SDL_Point p{ 300,0 };
	

	m_compIDVec.clear();

	characterFactory = new Princess();
	m_entities.push_back(characterFactory->CharA("Red", p, 0));
	m_entities.back()->Active(true);


	characterFactory = new BasicEnemy();

	
	for (int i = 0; i < 1; i++)
	{
		m_entities.push_back(characterFactory->CharC("Demon", SDL_Point{  }, 0));

		//m_entities.push_back(characterFactory->CharC("Demon", SDL_Point{ rand() % 812, rand() % 624 }, 0));

		m_entities.back()->Active(true);
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


void AiSystem::seek(int entityIndex, int pcKey, int mcKey, int seekKey, int attributeKey, float tarX, float tarY, int behaviour)
{


//	SDL_Point{ rand() % 812, rand() % 624 }, 0));
	
	float x = tarX - static_cast<PositionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(pcKey))->getX();
	float y = tarY - static_cast<PositionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(pcKey))->getY();

	float dist = magnitude(x, y);

	static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->setDistanceToDestination(dist);

	if (dist > static_cast<AttributesComponent*>(m_entities.at(entityIndex)->GetComponents()->at(attributeKey))->MovementSpeed() / 60.0f)
	{
		normalise(x, y);
		x *= static_cast<AttributesComponent*>(m_entities.at(entityIndex)->GetComponents()->at(attributeKey))->MovementSpeed();
		y *= static_cast<AttributesComponent*>(m_entities.at(entityIndex)->GetComponents()->at(attributeKey))->MovementSpeed();

		if (behaviour == 0)
		{
			static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setXVelocity(x);
			static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setYVelocity(y);
		}
		if (behaviour == 1)
		{
			static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setXVelocity(-x);
			static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setYVelocity(-y);
		}
	}



	//else
	//{
	//	static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setXVelocity(0);
	//	static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setYVelocity(0);
	//}
}


void AiSystem::Update()
{
	
}


void AiSystem::Wander(int entityIndex, int pcKey, int mcKey, int seekKey, int attributeKey)
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

	}


	//std::cout << "X: " << static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->getXDestination() << "  Y: " << static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->getYDestination() << std::endl;


	float x = static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->getXDestination() - static_cast<PositionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(pcKey))->getX();
	float y = static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->getYDestination() - static_cast<PositionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(pcKey))->getY();

	float dist = magnitude(x, y);

	static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->setDistanceToDestination(dist);

	//if (dist > static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->getSpeed() )
	//{
		normalise(x, y);
		x *= static_cast<AttributesComponent*>(m_entities.at(entityIndex)->GetComponents()->at(attributeKey))->MovementSpeed();
		y *= static_cast<AttributesComponent*>(m_entities.at(entityIndex)->GetComponents()->at(attributeKey))->MovementSpeed();

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

	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->ID() == "Spellcaster Enemy")
		{
			m_decisionTree->calculatePathNodes(m_decisionTree->m_RootNode);

		//	int decision = m_decisionTree->getDecision();

			int decision = 10;

			if (decision == 8 || decision == 9)
			{
				int tw = m_entities.at(i)->FindComponentIndex("attack");
				int tx = m_entities.at(i)->FindComponentIndex("movement");
				attack(i, tw, tx);
				//attack
			}

			else if (decision == 10 || decision == 11)
			{
				int tw = m_entities.at(i)->FindComponentIndex("PC"); //move index finding to spawn, 
				int tx = m_entities.at(i)->FindComponentIndex("movement");
				int ty = m_entities.at(i)->FindComponentIndex("seek");
				int tz = m_entities.at(i)->FindComponentIndex("attribute");
				
				float tarX = 0;
				float tarY = 0;

				for (int j = 0; j < m_entities.size(); j++)
				{
					if (m_entities.at(j)->ID() == "Princess")
					{
						//probably check for active here
						auto tar = m_entities.at(j)->FindComponent("PC");
						tarX = static_cast<PositionComponent*>(tar)->getX();
						tarY = static_cast<PositionComponent*>(tar)->getY();
						break;
					}
				}

				cout << tarX << endl;
				cout << tarY << endl;
				seek(i, tw , tx, ty, tz, tarX, tarY, 0); //refactor x and y to take in princess position or whatever player or whatever
				//seek
			}
		
			else if (decision == 12 || decision == 13)
			{
				//do nothing
			}
			else if (decision == 14 || decision == 15)
			{
				int tw = m_entities.at(i)->FindComponentIndex("PC");
				int tx = m_entities.at(i)->FindComponentIndex("movement");
				int ty = m_entities.at(i)->FindComponentIndex("seek");
				int tz = m_entities.at(i)->FindComponentIndex("attribute");

				float tarX = 0;
				float tarY = 0;

				for (int j = 0; j < m_entities.size(); j++)
				{
					if (m_entities.at(j)->ID() == "Princess")
					{
						//probably check for active here
						auto tar = m_entities.at(j)->FindComponent("PC");
						tarX = static_cast<PositionComponent*>(tar)->getX();
						tarY = static_cast<PositionComponent*>(tar)->getY();
						break;
					}
				}

				cout << tarX << endl;
				cout << tarY << endl;
				seek(i, tw, tx, ty, tz, tarX, tarY, 1); //refactor x and y to take in princess position or whatever player or whatever
														//seek
				//flee
			}
						//do Spellcaster enemy things
		}

	}
}

