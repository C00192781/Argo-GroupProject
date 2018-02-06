#include "Quad.h"


void Quadtree::clear() {
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

	nodes.push_back(new Quadtree(0, SDL_Rect{ x + subWidth, y, subWidth, subHeight }));
	nodes.push_back(new Quadtree(0, SDL_Rect{ x, y, subWidth, subHeight }));
	nodes.push_back(new Quadtree(0, SDL_Rect{ x, y + subHeight, subWidth, subHeight }));
	nodes.push_back(new Quadtree(0, SDL_Rect{ x + subWidth, y + subHeight, subWidth, subHeight }));
}


void Quadtree::init()
{

	nodes.push_back(new Quadtree(0, SDL_Rect{ 800,800,1,1 })); //these quads probably should be different
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
	if (entity->ID() == "Princess") //debug only
	{

		double verticalMidpoint = 0 + (bounds.w / 2.0f); //bounds.x + (bounds.w / 2.0f);

		double horizontalMidpoint = 0 + (bounds.h / 2.0f);//bounds.y + (bounds.h / 2.0f);

		auto temp = entity->GetComponents();
		auto tempx = static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getPosition().x;   ///SHE THINKS SHES IN THE WRONG QUADRANT HERE,

		auto tempy = static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getPosition().y;

		// Object can completely fit within the top quadrants
		bool topQuadrant = (static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getPosition().y <
			horizontalMidpoint && static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getPosition().y + 
			static_cast<SpriteComponent*>(entity->GetComponents()->at(1))->GetRect().h < horizontalMidpoint);
		// Object can completely fit within the bottom quadrants
		bool bottomQuadrant = (static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getPosition().y > horizontalMidpoint);

		// Object can completely fit within the left quadrants
		if (static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getPosition().x < verticalMidpoint && static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getPosition().x
			+ static_cast<SpriteComponent*>(entity->GetComponents()->at(1))->GetRect().w < verticalMidpoint) {
			if (topQuadrant) {
				index = 1;
				if (entity->ID() == "Princess")
				{
					cout << "topleft " << endl;
				}
			}
			else if (bottomQuadrant) {
				index = 2;
				if (entity->ID() == "Princess")
				{
					cout << "bottomleft" << endl;
				}
			}
		}
		// Object can completely fit within the right quadrants
		else if (static_cast<PositionComponent*>(entity->GetComponents()->at(0))->getPosition().x > verticalMidpoint) {
			if (topQuadrant) {
				index = 0;
				if (entity->ID() == "Princess")
				{
					cout << "topright" << endl;
				}
			}
			else if (bottomQuadrant) {
				index = 3;
				if (entity->ID() == "Princess")
				{
					cout << "bottomright" << endl;
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
		if (nodes.size() > 0 && nodes[0] == nullptr) { //
			split();
		}


		for (int i = 0; i < objects.size(); i++)
		{
			int index = getIndex(objects.at(i));

			if (nodes.size() > 0 && index != -1)
			{
				nodes.at(index)->insert(objects.at(i)); //

				objects.erase(objects.begin() + i);
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