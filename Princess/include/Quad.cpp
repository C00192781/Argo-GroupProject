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
	cout << "split " << endl;
	cout << "level: " << level << endl;


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


void Quadtree::init()
{
	int subWidth = (int)(bounds.w / 2);
	int subHeight = (int)(bounds.h / 2);
	int x = bounds.x;
	int y = bounds.y;

	nodes.push_back(new Quadtree(0, SDL_Rect{ x + subWidth, y, subWidth, subHeight }));
	nodes.push_back(new Quadtree(0, SDL_Rect{ x, y, subWidth, subHeight }));
	nodes.push_back(new Quadtree(0, SDL_Rect{ x, y + subHeight, subWidth, subHeight }));
	nodes.push_back(new Quadtree(0, SDL_Rect{ x + subWidth, y + subHeight, subWidth, subHeight }));
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

	// Object can completely fit within the top quadrants
	bool topQuadrant = (static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getY() <
		horizontalMidpoint && static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getY() + 
		static_cast<SpriteComponent*>(entity->GetComponents()->at(1))->GetRect().h < horizontalMidpoint);

	// Object can completely fit within the bottom quadrants
	bool bottomQuadrant = (static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getY() > horizontalMidpoint);

	// Object can completely fit within the left quadrants
	if (static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getX() < verticalMidpoint && static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getX()
		+ static_cast<SpriteComponent*>(entity->GetComponents()->at(1))->GetRect().w < verticalMidpoint) {
		if (topQuadrant) {
			index = 1;
			
			//cout << entity->ID() << "topleft " << endl;
		}
		else if (bottomQuadrant) {
			index = 2;

			//cout << entity->ID() << "bottomleft" << endl;
		}
	}
	// Object can completely fit within the right quadrants
	else if (static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getX() > verticalMidpoint) {
		if (topQuadrant) {
			index = 0;

			//cout << entity->ID() << "topright" << endl;
		}
		else if (bottomQuadrant) {
			index = 3;

			//cout << entity->ID() << "bottomright" << endl;
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

		//int i = 0;

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