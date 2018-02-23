#include "AISystem.h"
#include <time.h>

AiSystem::AiSystem(AStar * aStar)
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

	m_aStar = aStar;
	currentPlayer = 0;
	timer = 0;
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

	srand(time(NULL));


	int mod1 = rand() % 800;

	int mod2 = rand() % 600;

//	cout << "mod1 " << mod1 << endl;


	
	static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->setXDestination(mod2);

	static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->setYDestination(mod2);


	

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
		WeaponComponent* weaponComponent = static_cast<WeaponComponent*>(m_entities.at(entityIndex)->FindComponent("weapon"));
		float temp = weaponComponent->getTimeToAllowAttack();
	//	cout << "temp: " << temp << endl;
		MovementComponent* movementComponent = static_cast<MovementComponent*>(m_entities.at(entityIndex)->FindComponent("movement"));

		if (temp > -1)
		{
			temp -= m_time;
			weaponComponent->setAttacking(false);
			weaponComponent->setAllowAttack(true);
			//	cout << "case no atk" << endl;
		}
		else
		{
			temp = weaponComponent->getMaxTimeToAllowAttack();
			weaponComponent->setAttacking(true);
			weaponComponent->setAllowAttack(false);
			
		//	cout << "case atk " << endl;

		}
		movementComponent->setXVelocity(0);
		movementComponent->setYVelocity(0);
		weaponComponent->setTimeToAllowAttack(temp);
	}

	else //if player
	{

		WeaponComponent* weaponComponent = static_cast<WeaponComponent*>(m_playerEntities.at(entityIndex)->FindComponent("weapon"));
		float temp = weaponComponent->getTimeToAllowAttack();
	//	cout << "temp: " << temp << endl;
		MovementComponent* movementComponent = static_cast<MovementComponent*>(m_playerEntities.at(entityIndex)->FindComponent("movement"));

		if (temp > -0.4f)
		{
			temp -= m_time;
			weaponComponent->setAttacking(false);
			weaponComponent->setAllowAttack(true);
			//	cout << "case no atk" << endl;
		}
		else
		{
			temp = weaponComponent->getMaxTimeToAllowAttack();
			weaponComponent->setAttacking(true);
			weaponComponent->setAllowAttack(false);

		//	cout << "case atk " << endl;

		}
		movementComponent->setXVelocity(0);
		movementComponent->setYVelocity(0);
		weaponComponent->setTimeToAllowAttack(temp);

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
//	cout << deltaTime << endl;
	if (m_entities.empty())
	{
		int q = 5;
		q -= 5;
	}

	m_time = deltaTime;
	timer++;

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


			auto hpComp = m_playerEntities.at(i)->FindComponent("attribute");

			if (static_cast<AttributesComponent*>(hpComp)->Health() < 1)
			{
				m_playerEntities.at(i)->Active(false);
			}


			MovementComponent* movementComponent = static_cast<MovementComponent*>(m_playerEntities.at(i)->FindComponent("movement"));
			Component* tarAttribComp = nullptr;

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
							tarAttribComp = m_entities.at(j)->FindComponent("attribute");
						}

						else if (dist > magnitude(x, y))
						{
							dist = magnitude(x, y);
							tarY = tempY;
							tarX = tempX;
							tarIndex = j;
							tarAttribComp = m_entities.at(j)->FindComponent("attribute");
						}

					}
				}
			} //end ent for

	
				auto selfRange = 200;//static_cast<WeaponComponent*>(m_playerEntities.at(i)->FindComponent("weapon"))->getRange() * 10;;
				int enemyRange = 200; //defaulting

				if (!m_entities.empty() && m_entities.size() >= tarIndex)
				{
					if (m_entities.at(tarIndex)->FindComponent("weapon") != nullptr)
					{
						enemyRange = 200;//static_cast<WeaponComponent*>(m_entities.at(tarIndex)->FindComponent("weapon"))->getRange() * 10;
					}
				}

				//cout << "tarhp: " <<static_cast<AttributesComponent*>(tarAttribComp)->Health() << endl;

				//cout << "selfHPplayer: " <<static_cast<AttributesComponent*>(hpComp)->Health() << endl;

				if (tarAttribComp != nullptr && m_entities.at(tarIndex)->FindComponent("weapon") != nullptr && hpComp != nullptr)
				{
					enemyRange = static_cast<WeaponComponent*>(m_entities.at(tarIndex)->FindComponent("weapon"))->getRange() * 10;;
					m_decisionTree->calculatePathNodes(m_decisionTree->m_RootNode, dist, static_cast<AttributesComponent*>(tarAttribComp)->Health(), static_cast<AttributesComponent*>(hpComp)->Health(), selfRange, enemyRange); //make target HP and self HP gettable later,  hardcoded values for test purpose only.
				}
				else
				{
					m_decisionTree->calculatePathNodes(m_decisionTree->m_RootNode, dist, 1, 1, selfRange, 300); //make target HP and self HP gettable later,  hardcoded values for test purpose only.

				}

				////$$$$$$
				//if (tarAttribComp != nullptr && players.at(tarIndex)->FindComponent("weapon") != nullptr)
				//{
				//	enemyRange = static_cast<WeaponComponent*>(players.at(tarIndex)->FindComponent("weapon"))->getRange() * 10;;
				//	m_decisionTree->calculatePathNodes(m_decisionTree->m_RootNode, dist, static_cast<AttributesComponent*>(tarAttribComp)->Health(), static_cast<AttributesComponent*>(hpComp)->Health(), selfRange, enemyRange); //make target HP and self HP gettable later,  hardcoded values for test purpose only.
				//}
				//else
				//{
				//	m_decisionTree->calculatePathNodes(m_decisionTree->m_RootNode, dist, 2, static_cast<AttributesComponent*>(hpComp)->Health(), selfRange, 300); //make target HP and self HP gettable later,  hardcoded values for test purpose only.

				//}
				//int decision = m_decisionTree->getDecision();
				////$$$

			//	m_decisionTree->calculatePathNodes(m_decisionTree->m_RootNode, dist, 1, 8, selfRange, enemyRange); //make target HP and self HP gettable later,  hardcoded values for test purpose only.
			//	cout << "dist: " << dist << endl;
				int decision = m_decisionTree->getDecision();
					//	cout << "decision: " << decision << endl;
					// = 10;

				if (decision == 8 || decision == 9) //if hp adv and in range
				{
					int tw = m_playerEntities.at(i)->FindComponentIndex("weapon");
					int tx = m_playerEntities.at(i)->FindComponentIndex("movement");

					auto tp = m_playerEntities.at(i)->FindComponent("PC");

					int selfX = static_cast<PositionComponent*>(tp)->getX();

					int selfY = static_cast<PositionComponent*>(tp)->getY();
					//816, 624,
					movementComponent->setOrientation(atan2f(tarY - selfY, tarX - selfX)     * (180 / 3.14f) + 90);

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

					static_cast<WeaponComponent*>(m_playerEntities.at(i)->GetComponents()->at(tq))->setAttacking(false);
					static_cast<WeaponComponent*>(m_playerEntities.at(i)->GetComponents()->at(tq))->setAllowAttack(true);
																					//seek
				}

				else if (decision == 12 || decision == 13) //if no hp adv and out of range
				{
					auto move = m_playerEntities.at(i)->FindComponent("movement");

					static_cast<MovementComponent*>(move)->setXVelocity(0);
					static_cast<MovementComponent*>(move)->setYVelocity(0);
					int tq = m_playerEntities.at(i)->FindComponentIndex("weapon");

					static_cast<WeaponComponent*>(m_playerEntities.at(i)->GetComponents()->at(tq))->setAttacking(false);
					static_cast<WeaponComponent*>(m_playerEntities.at(i)->GetComponents()->at(tq))->setAllowAttack(true);

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

				//	cout << "RUN AWAY" << endl;
					seek(i, tw, tx, ty, tz, tarX, tarY, 1, m_playerEntities.at(i)->ID()); //RUN AWAY
					static_cast<WeaponComponent*>(m_playerEntities.at(i)->GetComponents()->at(tq))->setAttacking(false);
					static_cast<WeaponComponent*>(m_playerEntities.at(i)->GetComponents()->at(tq))->setAllowAttack(true);													//flee

				}
			} //end vector.empty

	} //end for player ################

	
	//BEGIN ENEMIES $$$

	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->ID() != "Player" && m_entities.at(i)->ID() != "Princess")
		{
			MovementComponent* movementComponent = static_cast<MovementComponent*>(m_entities.at(i)->FindComponent("movement"));
			


			auto hpComp = m_entities.at(i)->FindComponent("attribute");
			//mvoed
			if (static_cast<AttributesComponent*>(hpComp)->Health() < 1)
			{
				m_entities.at(i)->Active(false);
			}


			Component* tarAttribComp = nullptr;

			int tarIndex = 0; //-1?

	
			if (m_entities.at(i)->Active())
			{
				if (m_entities.at(i)->ID() == "Spellcaster Enemy" || m_entities.at(i)->ID() == "Melee Enemy" || m_entities.at(i)->ID() == "Ranged Enemy")
				{

					float tarX = 0;
					float tarY = 0;
					float dist = 0;

					for (int j = 0; j < players.size(); j++)
					{
						if (players.at(j)->ID() == "Player") //some sort of target discerning goes here later
						{
							if (players.at(j)->Active())
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
					}

				//	cout << dist << endl;
					int enemyRange = 100;
					//auto enemyRange = static_cast<WeaponComponent*>(m_playerEntities.at(i)->FindComponent("weapon"))->getRange();
					auto selfRange = 100;

					//cout << "playerHp: " << static_cast<AttributesComponent*>(hpComp)->Health() << endl;

					if (tarAttribComp != nullptr && players.at(tarIndex)->FindComponent("weapon") != nullptr && hpComp != nullptr)
					{ 
					//	enemyRange = static_cast<WeaponComponent*>(players.at(tarIndex)->FindComponent("weapon"))->getRange() * 10;
					//	selfRange = static_cast<WeaponComponent*>(m_entities.at(i)->FindComponent("weapon"))->getRange() * 10;
						m_decisionTree->calculatePathNodes(m_decisionTree->m_RootNode, dist, static_cast<AttributesComponent*>(tarAttribComp)->Health() / 4.0f, static_cast<AttributesComponent*>(hpComp)->Health(), selfRange, enemyRange); //make target HP and self HP gettable later,  hardcoded values for test purpose only.
					}
					else
					{
						m_decisionTree->calculatePathNodes(m_decisionTree->m_RootNode, dist, 1, 2, selfRange, 300); //make target HP and self HP gettable later,  hardcoded values for test purpose only.

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
						
						if (m_aStar->getCurrentMapType() == "Dungeon")
						{
							float playerX = 0;
							float playerY = 0;

							float targetNodeX = 0;
							float targetNodeY = 0;

							for (int j = 0; j < m_playerEntities.size(); j++)
							{

								float x = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(tw))->getX();
								float y = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(tw))->getY();

								Vec2f currentPosition = Vec2f{ x,y };

								if (timer == 0)
								{
									currentPlayer = rand() % (m_playerEntities.size()-1); 
									
									static_cast<SeekComponent*>(m_entities.at(i)->GetComponents()->at(ty))->setInitialization(false);
								}
								
								if (m_playerEntities.at(currentPlayer)->ID() == "Player")
								{
									auto tar = m_playerEntities.at(currentPlayer)->FindComponent("PC");

									playerX = static_cast<PositionComponent*>(tar)->getX();
									playerY = static_cast<PositionComponent*>(tar)->getY();

								}
								targetNodeX = static_cast<SeekComponent*>(m_entities.at(i)->GetComponents()->at(ty))->getXDestination();
								targetNodeY = static_cast<SeekComponent*>(m_entities.at(i)->GetComponents()->at(ty))->getYDestination();

								Vec2f targetNode = Vec2f{ targetNodeX, targetNodeY };

								Vec2f player = Vec2f{ playerX, playerY };

								if (static_cast<SeekComponent*>(m_entities.at(i)->GetComponents()->at(ty))->getInitialization() == false)
								{
									Vec2f initialTarget = m_aStar->searchNearestWaypoint(currentPosition);
									targetNode = m_aStar->getPosition(&player, &initialTarget);
									static_cast<SeekComponent*>(m_entities.at(i)->GetComponents()->at(ty))->setXDestination(targetNode.x);
									static_cast<SeekComponent*>(m_entities.at(i)->GetComponents()->at(ty))->setYDestination(targetNode.y);
									static_cast<SeekComponent*>(m_entities.at(i)->GetComponents()->at(ty))->setInitialization(true);
								}

								float distanceToOverallTarget = m_aStar->getDistanceToDestination(&currentPosition, &player);
								float distanceToNode = m_aStar->getDistanceToDestination(&currentPosition, &targetNode);

								if (distanceToNode < 5)
								{
									Vec2f player = Vec2f{ playerX, playerY };
									targetNode = m_aStar->getPosition(&player, &targetNode);
									static_cast<SeekComponent*>(m_entities.at(i)->GetComponents()->at(ty))->setXDestination(targetNode.x);
									static_cast<SeekComponent*>(m_entities.at(i)->GetComponents()->at(ty))->setYDestination(targetNode.y);
								}

								if (distanceToOverallTarget < distanceToNode || distanceToOverallTarget < 100)
								{
									targetNodeX = playerX;
									targetNodeY = playerY;
								}
							}
							seek(i, tw, tx, ty, tz, targetNodeX, targetNodeY, 0, m_entities.at(i)->ID()); //refactor x and y to take in princess position or whatever player or whatever
						}																			  //seek
						else
						{
							static_cast<SeekComponent*>(m_entities.at(i)->GetComponents()->at(ty))->setInitialization(false);
							seek(i, tw, tx, ty, tz, tarX, tarY, 0, m_entities.at(i)->ID());
						}
						if (timer >= 240)
						{
							timer = 0;
						}
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


		else if (m_entities.at(i)->ID() == "Princess")
		{
			//do princess things
			Wander(i, m_entities.at(i)->FindComponentIndex("PC") , m_entities.at(i)->FindComponentIndex("movement"), m_entities.at(i)->FindComponentIndex("seek"), m_entities.at(i)->FindComponentIndex("attribute"));
		}
	}

	m_playerEntities.clear();
	players.clear();
}

