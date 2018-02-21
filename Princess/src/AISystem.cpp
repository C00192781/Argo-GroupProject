#include "AISystem.h"
#include <time.h>

AiSystem::AiSystem()
{
	//m_thingy = 1;
	//add root node
	m_decisionTree->CreateRootNode(1);

	//add root node   the very first 'Question' or decision to be made
	//is monster health greater than player health?
	//m_decisionTree->CreateRootNode(1);

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


	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch2, 3, 6); //fix addnodes to support larger treesizes soontm.
	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch2, 3, 7);
	//	m_decisionTree->printLeafNodes(m_decisionTree->m_RootNode); //this worky workies
	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch1->NewBranch1, 4, 8);
	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch1->NewBranch1, 4, 9);

	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch1->NewBranch2, 5, 10); //move to init prolly
	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch1->NewBranch2, 5, 11);

	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch2->NewBranch1, 6, 12);
	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch2->NewBranch1, 6, 13);

	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch2->NewBranch2, 7, 14);
	m_decisionTree->AddNode1(m_decisionTree->m_RootNode->NewBranch2->NewBranch2, 7, 15);
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



//	SDL_Point p{ 300,0 };
//	
//
//	m_compIDVec.clear();
///*
//	characterFactory = new Princess();
//	m_entities.push_back(characterFactory->CharA("Red", p, 0));
//	m_entities.back()->Active(true);
//
//*/
//	characterFactory = new BasicEnemy();
//
//	
//	for (int i = 0; i < 6; i++)
//	{
//	//	m_entities.push_back(characterFactory->CharC("Demon", SDL_Point{ p.x + 20, p.y + 20 }, 0));
//
//		m_entities.push_back(characterFactory->CharC("Demon", SDL_Point{ rand() % 812, rand() % 624 }, 0));
//
//		m_entities.back()->Active(true);
//	}
//

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


void AiSystem::seek(int entityIndex, int pcKey, int mcKey, int seekKey, int attributeKey, float tarX, float tarY, int behaviour, string tag)
{

	if (tag != "Player")
	{

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

	}
	else
	{

		float x = tarX - static_cast<PositionComponent*>(m_playerEntities.at(entityIndex)->GetComponents()->at(pcKey))->getX();
		float y = tarY - static_cast<PositionComponent*>(m_playerEntities.at(entityIndex)->GetComponents()->at(pcKey))->getY();

		float dist = magnitude(x, y);

		static_cast<SeekComponent*>(m_playerEntities.at(entityIndex)->GetComponents()->at(seekKey))->setDistanceToDestination(dist);

		if (dist > static_cast<AttributesComponent*>(m_playerEntities.at(entityIndex)->GetComponents()->at(attributeKey))->MovementSpeed() / 60.0f)
		{
			normalise(x, y);
			x *= static_cast<AttributesComponent*>(m_playerEntities.at(entityIndex)->GetComponents()->at(attributeKey))->MovementSpeed();
			y *= static_cast<AttributesComponent*>(m_playerEntities.at(entityIndex)->GetComponents()->at(attributeKey))->MovementSpeed();

			if (behaviour == 0)
			{
				static_cast<MovementComponent*>(m_playerEntities.at(entityIndex)->GetComponents()->at(mcKey))->setXVelocity(x);
				static_cast<MovementComponent*>(m_playerEntities.at(entityIndex)->GetComponents()->at(mcKey))->setYVelocity(y);
			}
			if (behaviour == 1)
			{
				static_cast<MovementComponent*>(m_playerEntities.at(entityIndex)->GetComponents()->at(mcKey))->setXVelocity(-x);
				static_cast<MovementComponent*>(m_playerEntities.at(entityIndex)->GetComponents()->at(mcKey))->setYVelocity(-y);
			}
		}
	}

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

	normalise(x, y);
	x *= static_cast<AttributesComponent*>(m_entities.at(entityIndex)->GetComponents()->at(attributeKey))->MovementSpeed();
	y *= static_cast<AttributesComponent*>(m_entities.at(entityIndex)->GetComponents()->at(attributeKey))->MovementSpeed();

	static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setXVelocity(x);
	static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setYVelocity(y);


}




void AiSystem::attack(int entityIndex, int attackKey, int mcKey, string tag)
{
	if (tag != "Player")
	{
		static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setXVelocity(0);
		static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setYVelocity(0);
		static_cast<WeaponComponent*>(m_entities.at(entityIndex)->GetComponents()->at(attackKey))->setAttacking(true);
		static_cast<WeaponComponent*>(m_entities.at(entityIndex)->GetComponents()->at(attackKey))->setAllowAttack(false);
	}
	else
	{
		static_cast<MovementComponent*>(m_playerEntities.at(entityIndex)->GetComponents()->at(mcKey))->setXVelocity(0);
		static_cast<MovementComponent*>(m_playerEntities.at(entityIndex)->GetComponents()->at(mcKey))->setYVelocity(0);
		static_cast<WeaponComponent*>(m_playerEntities.at(entityIndex)->GetComponents()->at(attackKey))->setAttacking(true);
		static_cast<WeaponComponent*>(m_entities.at(entityIndex)->GetComponents()->at(attackKey))->setAllowAttack(false);
	}

	
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

void AiSystem::Update(float deltaTime, std::vector<Entity*> players)
{

	if (m_entities.empty())
	{
		int q = 5;
		q -= 5;
	}

	m_time = deltaTime;

	//std::vector<Entity*> m_playerAIEntities;

	for (int i = 0; i < players.size(); i++)
	{
		//m_playerEntities.push_back(players.at(i));
		
		int check = players.at(i)->FindComponentIndex("AIL");

		if (check != -1)
		{
			m_playerEntities.push_back(players.at(i));
		}
	}


	for (int i = 0; i < m_playerEntities.size(); i++)
	{
		if (!m_entities.empty()) //dont check empty vectors for stuff
		{
			float tarX = 0;
			float tarY = 0;
			float dist = 0;

			int tarIndex = -1;

			for (int j = 0; j < m_entities.size(); j++)
			{
				if (m_entities.at(j)->Active())
				{
					if (m_entities.at(j)->ID() == "Spellcaster Enemy" || m_entities.at(j)->ID() == "Melee Enemy" || m_entities.at(j)->ID() == "Ranged Enemy")
					{

						auto tar = m_entities.at(j)->FindComponent("PC");
						int tempX = static_cast<PositionComponent*>(tar)->getX();
						int tempY = static_cast<PositionComponent*>(tar)->getY();

						float x = tempX - static_cast<PositionComponent*>(m_playerEntities.at(i)->FindComponent("PC"))->getX();
						float y = tempY - static_cast<PositionComponent*>(m_playerEntities.at(i)->FindComponent("PC"))->getY();

						if (dist == 0)
						{
							dist = magnitude(x, y);
							tarX = tempX;
							tarY = tempY;
							tarIndex = j;
						}

						else if (dist > magnitude(x, y))
						{
							dist = magnitude(x, y);
							tarY = tempY;
							tarX = tempX;
							tarIndex = j;
						}

					}
				}
			} //end ent for

	
				auto selfRange = static_cast<WeaponComponent*>(m_playerEntities.at(i)->FindComponent("weapon"))->getRange() * 10;;
				int enemyRange = 200; //defaulting

				if (!m_entities.empty() && m_entities.size() >= tarIndex)
				{
					if (m_entities.at(tarIndex)->FindComponent("weapon") != nullptr)
					{
						enemyRange = static_cast<WeaponComponent*>(m_entities.at(tarIndex)->FindComponent("weapon"))->getRange() * 10;
					}
				}
				m_decisionTree->calculatePathNodes(m_decisionTree->m_RootNode, dist, 1, 8, selfRange, enemyRange); //make target HP and self HP gettable later,  hardcoded values for test purpose only.
			//	cout << "dist: " << dist << endl;
				int decision = m_decisionTree->getDecision();
				//		cout << "decision: " << decision << endl;
					// = 10;

				if (decision == 8 || decision == 9) //if hp adv and in range
				{
					int tw = m_playerEntities.at(i)->FindComponentIndex("weapon");
					int tx = m_playerEntities.at(i)->FindComponentIndex("movement");

				

					attack(i, tw, tx, m_playerEntities.at(i)->ID());
					//attack
				}

				else if (decision == 10 || decision == 11) //if hp adv and out of range
				{
					int tw = m_playerEntities.at(i)->FindComponentIndex("PC"); //note:move index finding to spawn, 
					int tx = m_playerEntities.at(i)->FindComponentIndex("movement");
					int ty = m_playerEntities.at(i)->FindComponentIndex("seek");
					int tz = m_playerEntities.at(i)->FindComponentIndex("attribute");
					int tq = m_playerEntities.at(i)->FindComponentIndex("weapon");

					seek(i, tw, tx, ty, tz, tarX, tarY, 0, m_playerEntities.at(i)->ID()); //refactor x and y to take in princess position or whatever player or whatever

					static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(tq))->setAttacking(false);
					static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(tq))->setAllowAttack(true);
																					//seek
				}

				else if (decision == 12 || decision == 13) //if no hp adv and out of range
				{
					auto move = m_playerEntities.at(i)->FindComponent("movement");

					static_cast<MovementComponent*>(move)->setXVelocity(0);
					static_cast<MovementComponent*>(move)->setYVelocity(0);
					int tq = m_playerEntities.at(i)->FindComponentIndex("weapon");

					static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(tq))->setAttacking(false);
					static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(tq))->setAllowAttack(true);

					//	static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(tx)->setYVelocity(0));
					//do nothing
				}
				else if (decision == 14 || decision == 15) //if no hp adv and in range
				{
					int tw = m_playerEntities.at(i)->FindComponentIndex("PC"); //note:move index finding to spawn, 
					int tx = m_playerEntities.at(i)->FindComponentIndex("movement");
					int ty = m_playerEntities.at(i)->FindComponentIndex("seek");
					int tz = m_playerEntities.at(i)->FindComponentIndex("attribute");
					int tq = m_playerEntities.at(i)->FindComponentIndex("weapon");


					seek(i, tw, tx, ty, tz, tarX, tarY, 1, m_playerEntities.at(i)->ID()); //refactor x and y to take in princess position or whatever player or whatever
					static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(tq))->setAttacking(false);
					static_cast<WeaponComponent*>(m_entities.at(i)->GetComponents()->at(tq))->setAllowAttack(true);													//flee

				}
			} //end vector.empty

	} //end for player

	
	//BEGIN ENEMIES $$$

	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->ID() != "Player")
		{
			MovementComponent* movementComponent = static_cast<MovementComponent*>(m_entities.at(i)->FindComponent("movement"));
			


			auto hpComp = m_entities.at(i)->FindComponent("attribute");

			Component* tarAttribComp = nullptr;

			int tarIndex = 0; //-1?

			if (static_cast<AttributesComponent*>(hpComp)->Health() < 1)
			{
				m_entities.at(i)->Active(false);
			}

			if (m_entities.at(i)->Active())
			{

				if (m_entities.at(i)->ID() == "Spellcaster Enemy" || m_entities.at(i)->ID() == "Melee Enemy" || m_entities.at(i)->ID() == "Ranged Enemy")
				{

					float tarX = 0;
					float tarY = 0;
					float dist = 0;

					for (int j = 0; j < players.size(); j++)
					{
						if (players.at(j)->ID() == "Player" && players.at(j)->Active()) //some sort of target discerning goes here later
						{
							auto tar = players.at(j)->FindComponent("PC");
							int tempX = static_cast<PositionComponent*>(tar)->getX();
							int tempY = static_cast<PositionComponent*>(tar)->getY();

							float x = tempX - static_cast<PositionComponent*>(m_entities.at(i)->FindComponent("PC"))->getX();
							float y = tempY - static_cast<PositionComponent*>(m_entities.at(i)->FindComponent("PC"))->getY();

							

							if (dist == 0)
							{
								dist = magnitude(x, y);
								tarX = tempX;
								tarY = tempY;
								tarIndex = j;
								tarAttribComp = players.at(j)->FindComponent("attribute");
							}

							else if (dist > magnitude(x, y))
							{
								dist = magnitude(x, y);
								tarY = tempY;
								tarX = tempX;
								tarIndex = j;
								tarAttribComp = players.at(j)->FindComponent("attribute");
							}
							
						}
					}

				//	cout << dist << endl;
					int enemyRange = 100;
					//auto enemyRange = static_cast<WeaponComponent*>(m_playerEntities.at(i)->FindComponent("weapon"))->getRange();

					auto selfRange = static_cast<WeaponComponent*>(m_entities.at(i)->FindComponent("weapon"))->getLife();

					//cout << "playerHp: " << static_cast<AttributesComponent*>(hpComp)->Health() << endl;

					if (tarAttribComp != nullptr && players.at(tarIndex)->FindComponent("weapon") != nullptr)
					{
						enemyRange = static_cast<WeaponComponent*>(players.at(tarIndex)->FindComponent("weapon"))->getLife();
						m_decisionTree->calculatePathNodes(m_decisionTree->m_RootNode, dist, static_cast<AttributesComponent*>(tarAttribComp)->Health(), static_cast<AttributesComponent*>(hpComp)->Health(), selfRange, enemyRange); //make target HP and self HP gettable later,  hardcoded values for test purpose only.
					}
					else
					{
						m_decisionTree->calculatePathNodes(m_decisionTree->m_RootNode, dist, 2, static_cast<AttributesComponent*>(hpComp)->Health(), selfRange, 300); //make target HP and self HP gettable later,  hardcoded values for test purpose only.

					}
					int decision = m_decisionTree->getDecision();
					//	cout << "decision: " << decision << endl;
					   // = 10;

					if (decision == 8 || decision == 9) //if hp adv and in range
					{
						int tw = m_entities.at(i)->FindComponentIndex("weapon");
						int tx = m_entities.at(i)->FindComponentIndex("movement");

						auto tp = m_entities.at(i)->FindComponent("PC");

						int selfX = static_cast<PositionComponent*>(tp)->getX();

						int selfY = static_cast<PositionComponent*>(tp)->getY();
						//816, 624,
						movementComponent->setOrientation(atan2f(tarY - selfY , tarX - selfX)     * (180 / 3.14f) + 90);

						attack(i, tw, tx, m_entities.at(i)->ID());
						//attack
					}

					else if (decision == 10 || decision == 11) //if hp adv and out of range
					{
						int tw = m_entities.at(i)->FindComponentIndex("PC"); //note:move index finding to spawn, 
						int tx = m_entities.at(i)->FindComponentIndex("movement");
						int ty = m_entities.at(i)->FindComponentIndex("seek");
						int tz = m_entities.at(i)->FindComponentIndex("attribute");

						seek(i, tw, tx, ty, tz, tarX, tarY, 0, m_entities.at(i)->ID()); //refactor x and y to take in princess position or whatever player or whatever
						//seek
					}

					else if (decision == 12 || decision == 13) //if no hp adv and out of range
					{
						auto move = m_entities.at(i)->FindComponent("movement");

						static_cast<MovementComponent*>(move)->setXVelocity(0);
						static_cast<MovementComponent*>(move)->setYVelocity(0);

						//	static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(tx)->setYVelocity(0));
							//do nothing
					}
					else if (decision == 14 || decision == 15) //if no hp adv and in range
					{
						int tw = m_entities.at(i)->FindComponentIndex("PC"); //note:move index finding to spawn, 
						int tx = m_entities.at(i)->FindComponentIndex("movement");
						int ty = m_entities.at(i)->FindComponentIndex("seek");
						int tz = m_entities.at(i)->FindComponentIndex("attribute");


						seek(i, tw, tx, ty, tz, tarX, tarY, 1, m_entities.at(i)->ID()); //refactor x and y to take in princess position or whatever player or whatever
																//flee

					}

				}	//end active enemy things

			}
		} //end not player

	}

	m_playerEntities.clear();
	players.clear();
}

