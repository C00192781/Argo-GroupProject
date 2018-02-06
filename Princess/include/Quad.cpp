#include "Quad.h"


//#pragma once
//#include "stdafx.h"
//#include <list>
//#include "Entity.h"
//using namespace std;
//
//class Quadtree
//{
//
//public:
//	Quadtree(int pLevel, SDL_Rect pBounds)
//	{
//		level = pLevel;
//		bounds = pBounds;
//		//nodes = new Quadtree[4];
//	}
//
//private:
//	int MAX_OBJECTS = 10;
//	int MAX_LEVELS = 5;
//
//	int level;
//	std::vector<Entity*> objects;
//	SDL_Rect bounds;
//	std::vector<Quadtree*> nodes;
//
//	/*
//	* Constructor
//	*/
//
//};

/*
* Clears the quadtree
*/

void Quadtree::clear() {
	objects.clear();
	nodes.clear();
	/*for (int i = 0; i < nodes.size; i++) {
		if (nodes[i] != null) {
			nodes[i].clear();
			nodes[i] = null;
		}
	}*/
}

/*
* Splits the node into 4 subnodes
*/

void Quadtree::split() 
{

	int subWidth = (int)(bounds.w / 2);
	int subHeight = (int)(bounds.h / 2);
	int x = bounds.x;
	int y = bounds.y;

	nodes.clear();

	nodes.push_back(new Quadtree(0, SDL_Rect{ x + subWidth, y, subWidth, subHeight }));
	nodes.push_back(new Quadtree(0, SDL_Rect{ x, y, subWidth, subHeight }));
	nodes.push_back(new Quadtree(0, SDL_Rect{ x, y + subHeight, subWidth, subHeight }));
	nodes.push_back(new Quadtree(0, SDL_Rect{ x + subWidth, y + subHeight, subWidth, subHeight }));

	//nodes[0] = new Quadtree(level + 1, new Rectangle(x + subWidth, y, subWidth, subHeight));
	//nodes[1] = new Quadtree(level + 1, new Rectangle(x, y, subWidth, subHeight));
	//nodes[2] = new Quadtree(level + 1, new Rectangle(x, y + subHeight, subWidth, subHeight));
	//nodes[3] = new Quadtree(level + 1, new Rectangle(x + subWidth, y + subHeight, subWidth, subHeight));
}


void Quadtree::init()
{
	nodes.push_back(new Quadtree(0, SDL_Rect{ 800,800,1,1 }));
	nodes.push_back(new Quadtree(0, SDL_Rect{ 800,800,1,1 }));
	nodes.push_back(new Quadtree(0, SDL_Rect{ 800,800,1,1 }));
	nodes.push_back(new Quadtree(0, SDL_Rect{ 800,800,1,1 }));
}

/*
* Determine which node the object belongs to. -1 means
* object cannot completely fit within a child node and is part
* of the parent node
*/
int Quadtree::getIndex(Entity* entity)
{

	int index = -1;
	double verticalMidpoint = bounds.x + (bounds.w / 2.0f);

	double horizontalMidpoint = bounds.y + (bounds.h / 2.0f);

	//static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->getXDestination()

	

	//static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getPosition().x;

	auto temp = entity->GetComponents();
	// Object can completely fit within the top quadrants
	bool topQuadrant = (static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getPosition().y <
		horizontalMidpoint && static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getPosition().y + static_cast<SpriteComponent*>(entity->GetComponents()->at(1))->GetRect().h < horizontalMidpoint);
	// Object can completely fit within the bottom quadrants
	bool bottomQuadrant = (static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getPosition().y > horizontalMidpoint);

	// Object can completely fit within the left quadrants
	if (static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getPosition().x < verticalMidpoint && static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getPosition().x 
		+ static_cast<SpriteComponent*>(entity->GetComponents()->at(1))->GetRect().w < verticalMidpoint) {
		if (topQuadrant) {
			index = 1;
		}
		else if (bottomQuadrant) {
			index = 2;
		}
	}
	// Object can completely fit within the right quadrants
	else if (static_cast<PositionComponent*>(entity->GetComponents()->at(0))->getPosition().x > verticalMidpoint) {
		if (topQuadrant) {
			index = 0;
		}
		else if (bottomQuadrant) {
			index = 3;
		}
	}

	return index;
}

/*
* Insert the object into the quadtree. If the node
* exceeds the capacity, it will split and add all
* objects to their corresponding nodes.
*/

void Quadtree::insert(Entity* entities) 
{
	
	//if (nodes.size() > 0)
	//{
	//	std::cout << "NORTH KOREA BEST KOREA" << endl;
	//}


	if (nodes.size() > 0 && nodes[0] != nullptr )
	{
		int index = getIndex(entities);


		if (index != -1) {
			nodes.at(index)->insert(entities);

			return;
		}
	}

	objects.push_back(entities);

	if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS) 
	{
		if (nodes[0] == nullptr) { //really???????????????$$$$$$$$$$$$$$$$$$$$$$$$$$$$
			split();
		}


		for (int i = 0; i < objects.size(); i++)
		{
			int index = getIndex(objects.at(i));

			if (index != -1)
			{
				//objects.erase()
				nodes.at(index)->insert(objects.at(i)); //at index???

				objects.erase(objects.begin() + i);
				//nodes.at(i)->insert(objects.);
			}

		}
		

		/*	int index = getIndex(objects.get(i));
			if (index != -1) {
				nodes[index].insert(objects.remove(i));
			}
			else {
				i++;*/
		
	}
}


/*
* Return all objects that could collide with the given object
*/
std::vector<Entity*> Quadtree::retrieve(std::vector<Entity*> returnObjects, Entity* entity) {

	if (entity->ID() == "Princess")
	{
 		int q = 5;
		q -= 5;
	}



	int index = getIndex(entity);
	if (index != -1 && nodes.size() != 0 && nodes[0] != nullptr) 
	{
		nodes.at(index)->retrieve(returnObjects, entity);
	}

	for (auto i = objects.begin(), e = objects.end(); i != e; i++)
	{
	//	auto tempid = (*i)->ID();

	
		returnObjects.push_back(*i);
//		returnObjects.push_back(objects);
	}

	return returnObjects;
}