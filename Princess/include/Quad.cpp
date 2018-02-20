#include "Quad.h"

Quadtree::~Quadtree()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		delete nodes.at(i);
	}
<<<<<<< HEAD
	nodes.clear();
}

void Quadtree::clear()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		delete nodes.at(i);
	}

	objects.clear();
	nodes.clear();
}

void Quadtree::split()
=======
	nodes.clear();
}

void Quadtree::clear()
>>>>>>> master
{
	for (int i = 0; i < nodes.size(); i++)
	{
		delete nodes.at(i);
	}

	objects.clear();
	nodes.clear();
<<<<<<< HEAD

	nodes.push_back(new Quadtree(level + 1, SDL_Rect{ x + subWidth, y, subWidth, subHeight }));
	nodes.push_back(new Quadtree(level + 1, SDL_Rect{ x, y, subWidth, subHeight }));
	nodes.push_back(new Quadtree(level + 1, SDL_Rect{ x, y + subHeight, subWidth, subHeight }));
	nodes.push_back(new Quadtree(level + 1, SDL_Rect{ x + subWidth, y + subHeight, subWidth, subHeight }));
=======
>>>>>>> master
}

void Quadtree::split()
{
	int subWidth = (int)(bounds.w / 2);
	int subHeight = (int)(bounds.h / 2);
	int x = bounds.x;
	int y = bounds.y;

	nodes.clear();

	nodes.push_back(new Quadtree(level + 1, SDL_Rect{ x + subWidth, y, subWidth, subHeight }));
	nodes.push_back(new Quadtree(level + 1, SDL_Rect{ x, y, subWidth, subHeight }));
	nodes.push_back(new Quadtree(level + 1, SDL_Rect{ x, y + subHeight, subWidth, subHeight }));
	nodes.push_back(new Quadtree(level + 1, SDL_Rect{ x + subWidth, y + subHeight, subWidth, subHeight }));
}

/*
* Determine which node the object belongs to. -1 means
* object cannot completely fit within a child node and is part
* of the parent node
*/
int Quadtree::getIndex(Entity* entity)
{
	int index = -1;

	for (int i = 0; i < entity->GetComponents()->size(); i++)
	{
		if (entity->GetComponents()->at(i)->Type() == "collision")
		{
			CollisionComponent* collisionComponent = static_cast<CollisionComponent*>(entity->GetComponents()->at(i));
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> master

			double verticalMidpoint = bounds.x + (bounds.w / 2.0f);
			double horizontalMidpoint = bounds.y + (bounds.h / 2.0f);

			bool topQuadrant = (collisionComponent->getY() < horizontalMidpoint
				&& collisionComponent->getY() + collisionComponent->getHeight() < horizontalMidpoint);

			bool bottomQuadrant = (collisionComponent->getY() > horizontalMidpoint);

			if (collisionComponent->getX() < verticalMidpoint &&
				collisionComponent->getX() + collisionComponent->getWidth() < verticalMidpoint)
			{
				if (topQuadrant) {
					index = 1;
				}
				else if (bottomQuadrant) {
					index = 2;
				}
			}
			else if (collisionComponent->getX() > verticalMidpoint)
			{
				if (topQuadrant) {
					index = 0;
				}
				else if (bottomQuadrant) {
					index = 3;
				}
			}
<<<<<<< HEAD

=======
			return index;
=======

			double verticalMidpoint = bounds.x + (bounds.w / 2.0f);
			double horizontalMidpoint = bounds.y + (bounds.h / 2.0f);

			bool topQuadrant = (collisionComponent->getY() < horizontalMidpoint
				&& collisionComponent->getY() + collisionComponent->getHeight() < horizontalMidpoint);

			bool bottomQuadrant = (collisionComponent->getY() > horizontalMidpoint);

			if (collisionComponent->getX() < verticalMidpoint &&
				collisionComponent->getX() + collisionComponent->getWidth() < verticalMidpoint)
			{
				if (topQuadrant) {
					index = 1;
				}
				else if (bottomQuadrant) {
					index = 2;
				}
			}
			else if (collisionComponent->getX() > verticalMidpoint)
			{
				if (topQuadrant) {
					index = 0;
				}
				else if (bottomQuadrant) {
					index = 3;
				}
			}

>>>>>>> master
			if (entity->ID() == "Player")
			{
				std::cout << level;
			}
<<<<<<< HEAD
		}
		return index;
	}
=======
>>>>>>> master
		}
		return index;
	}
<<<<<<< HEAD
	return index;
=======
>>>>>>> master
>>>>>>> master
}

/*
* Insert the object into the quadtree. If the node
* exceeds the capacity, it will split and add all
* objects to their corresponding nodes.
*/

void Quadtree::insert(Entity* entity) 
{
	if (!nodes.empty())
	{
		int index = getIndex(entity);


		if (index != -1) {
			nodes.at(index)->insert(entity);
			return;
		}
	}

	objects.push_back(entity);

	if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS) 
	{
		if (nodes.empty()) 
		{
			split();
		}

<<<<<<< HEAD
		//int i = 0;

=======
>>>>>>> master
		for (int i = 0; i < objects.size();)
		{
			int index = getIndex(objects.at(i));

			if (index != -1)
			{
				nodes.at(index)->insert(objects.at(i)); //

				objects.erase(objects.begin() + i);
			}
			else
			{
				i++;
			}
		}
	}
}


/*
* Return all objects that could collide with the given object
*/
std::vector<Entity*> Quadtree::retrieve(std::vector<Entity*> &returnObjects, Entity* entity) {


	int index = getIndex(entity);
	if (index != -1 && !nodes.empty()) 
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