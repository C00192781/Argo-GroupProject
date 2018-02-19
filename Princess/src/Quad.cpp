#include "Quad.h"

Quadtree::~Quadtree()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		delete nodes.at(i);
	}
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
	if (!nodes.empty())
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
		if (nodes.empty())
		{
			split();
		}

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
		// cuts down for loop checks
		if (!((*i)->ID() == "Spellcaster Enemy" && entity->ID() == "Spellcaster Enemy") && !((*i)->ID() == "Projectile" && entity->ID() == "Projectile"))
		{
			returnObjects.push_back(*i);
		}
	}

	return returnObjects;
}