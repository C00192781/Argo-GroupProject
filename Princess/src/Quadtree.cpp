#include "Quadtree.h"

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

void Quadtree::split() {
	int subWidth = (int)(bounds.w / 2);
	int subHeight = (int)(bounds.h / 2);
	int x = bounds.x;
	int y = bounds.y;

	nodes[0] = std::shared_ptr<Quadtree>(new Quadtree(level + 1, SDL_Rect{ x + subWidth, y, subWidth, subHeight }));
	nodes[1] = std::shared_ptr<Quadtree>(new Quadtree(level + 1, SDL_Rect{ x, y, subWidth, subHeight }));
	nodes[2] = std::shared_ptr<Quadtree>(new Quadtree(level + 1, SDL_Rect{ x, y + subHeight, subWidth, subHeight }));
	nodes[3] = std::shared_ptr<Quadtree>(new Quadtree(level + 1, SDL_Rect{ x + subWidth, y + subHeight, subWidth, subHeight }));
}


void Quadtree::init()
{
	nodes.push_back(std::shared_ptr<Quadtree>(new Quadtree(0, SDL_Rect{ 800,800,1,1 })));
	nodes.push_back(std::shared_ptr<Quadtree>(new Quadtree(0, SDL_Rect{ 800,800,1,1 })));
	nodes.push_back(std::shared_ptr<Quadtree>(new Quadtree(0, SDL_Rect{ 800,800,1,1 })));
	nodes.push_back(std::shared_ptr<Quadtree>(new Quadtree(0, SDL_Rect{ 800,800,1,1 })));
}

/*
* Determine which node the object belongs to. -1 means
* object cannot completely fit within a child node and is part
* of the parent node
*/
int Quadtree::getIndex(std::shared_ptr<Entity> entity)
{

	int index = -1;
	double verticalMidpoint = bounds.x + (bounds.w / 2.0f);

	double horizontalMidpoint = bounds.y + (bounds.h / 2.0f);

	//static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->getXDestination()



	std::static_pointer_cast<RectangleComponent>(entity->GetComponents()->at(2))->getPosition().x;

	auto temp = entity->GetComponents();
	// Object can completely fit within the top quadrants
	bool topQuadrant = (std::static_pointer_cast<RectangleComponent>(entity->GetComponents()->at(2))->getPosition().y <
		horizontalMidpoint && std::static_pointer_cast<RectangleComponent>(entity->GetComponents()->at(2))->getPosition().y + std::static_pointer_cast<RectangleComponent>(entity->GetComponents()->at(1))->getHeight() < horizontalMidpoint);
	// Object can completely fit within the bottom quadrants
	bool bottomQuadrant = (std::static_pointer_cast<RectangleComponent>(entity->GetComponents()->at(2))->getPosition().y > horizontalMidpoint);

	// Object can completely fit within the left quadrants
	if (std::static_pointer_cast<RectangleComponent>(entity->GetComponents()->at(2))->getPosition().x < verticalMidpoint && std::static_pointer_cast<RectangleComponent>(entity->GetComponents()->at(2))->getPosition().x
		+ std::static_pointer_cast<RectangleComponent>(entity->GetComponents()->at(1))->getWidth() < verticalMidpoint) {
		if (topQuadrant) {
			index = 1;
		}
		else if (bottomQuadrant) {
			index = 2;
		}
	}
	// Object can completely fit within the right quadrants
	else if (std::static_pointer_cast<RectangleComponent>(entity->GetComponents()->at(0))->getPosition().x > verticalMidpoint) {
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

void Quadtree::insert(std::shared_ptr<Entity> entities)
{

	//if (nodes.size() > 0)
	//{
	//	std::cout << "NORTH KOREA BEST KOREA" << endl;
	//}


	if (nodes.size() > 0 && nodes[0] != nullptr)
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
		if (nodes[0] == nullptr) {
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
std::vector<std::shared_ptr<Entity>> Quadtree::retrieve(std::vector<std::shared_ptr<Entity>> returnObjects, std::shared_ptr<Entity> entity) {

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

	returnObjects.insert(returnObjects.end(), objects.begin(), objects.end());
	//for (auto i = objects.begin(), e = objects.end(); i != e; i++)
	//{
	//	auto tempid = (*i)->ID();
	//
	//
	//	returnObjects.push_back(*i);
	//	//		returnObjects.push_back(objects);
	//}

	return returnObjects;
}

//std::vector<Entity*> Quadtree::retrieve(std::vector<Entity*> entities, Entity* e)
//{
//	int i = getIndex(e);
//
//	if (i != -1 && m_nodes[0] != NULL)
//	{
//		m_nodes[i]->retrieve(entities, e);
//	}
//
//	// adds all possible collidable objects with the given object
//	entities.insert(entities.end(), m_entities.begin(), m_entities.end());
//
//	return m_entities;
//}





//#include "Quadtree.h"
//
//Quadtree::Quadtree(int depth, SDL_Rect bounds)
//{
//	m_currentNodeDepth = depth;
//	bounds = m_bounds;
//}
//
//void Quadtree::init()
//{
//	for (int i = 0; i < 4; i++)
//	{
//		m_nodes.push_back(new Quadtree(0, SDL_Rect{ 0, 0, 0, 0 }));
//	}
//}
//
//void Quadtree::insert(Entity *e)
//{
//	// if there are no child nodes
//	if (m_nodes.size() > 0 && m_nodes.at(0) != NULL)
//	{
//		int i = getIndex(e); // check if the entity fits inside any of the quadrants
//
//		if (i != -1) // if it fits in a quadrant
//		{
//			m_nodes.at(i)->insert(e);
//			return; // breaks out of funtion once inserted
//		}
//	}
//
//	// adds to node
//	m_entities.push_back(e);
//
//	if (m_entities.size() > m_maxEntities && m_currentNodeDepth < m_maxSubnodeDepth)
//	{
//		if (m_nodes.size() > 0 && m_nodes.at(0) == NULL)
//		//if (m_nodes.at(0) == NULL)
//		{
//			split();
//		}
//
//		int i = 0;
//
//		//while (i < m_entities.size())
//		for (int i = 0; i < m_entities.size(); i++)
//		{
//			int index = getIndex(m_entities.at(i));
//
//			if (index != -1)
//			{
//				m_nodes.at(index)->insert(m_entities.at(i));
//				m_entities.erase(m_entities.begin() + i);
//			}
//			//else
//			//{
//			//	i++;
//			//}
//		}
//	}
//}
//
//void Quadtree::split()
//{
//	int w = m_bounds.w / 2;
//	int h = m_bounds.h / 2;
//
//	// splits parent node into 4 child nodes
//	m_nodes[0] = new Quadtree(m_currentNodeDepth + 1, SDL_Rect{ m_bounds.x + w, m_bounds.y, w, h });
//	m_nodes[1] = new Quadtree(m_currentNodeDepth + 1, SDL_Rect{ m_bounds.x, m_bounds.y, w, h });
//	m_nodes[2] = new Quadtree(m_currentNodeDepth + 1, SDL_Rect{ m_bounds.x, m_bounds.y + h, w, h });
//	m_nodes[3] = new Quadtree(m_currentNodeDepth + 1, SDL_Rect{ m_bounds.x + w, m_bounds.y + h, w, h });
//}
//
//std::vector<Entity*> Quadtree::retrieve(std::vector<Entity*> entities, Entity* e)
//{
//	int i = getIndex(e);
//
//	if (i != -1 && m_nodes[0] != NULL)
//	{
//		m_nodes[i]->retrieve(entities, e);
//	}
//
//	// adds all possible collidable objects with the given object
//	entities.insert(entities.end(), m_entities.begin(), m_entities.end());
//
//	return m_entities;
//}
//
//int Quadtree::getIndex(Entity *e)
//{
//	int index = -1; // returns -1 if it doesn't fit in any quadrants
//
//	int rectKey = -1;
//
//	// find rectangle component
//	for (int i = 0; i < e->GetComponents()->size(); i++)
//	{
//		if (e->GetComponents()->at(i)->Type() == 




//rectangle")
//		{
//			rectKey = i;
//		}
//	}
//
//	// get midpoints on quadrant
//	float xMidpoint = (float)m_bounds.x + ((float)m_bounds.w / 2);
//	float yMidpoint = (float)m_bounds.x + ((float)m_bounds.w / 2);
//
//	// check if entity fits in the top quadrants
//	bool topQuadrant = (std::static_pointer_cast<RectangleComponent>(e->GetComponents()->at(rectKey))->getPosition().y < yMidpoint
//		&& std::static_pointer_cast<RectangleComponent>(e->GetComponents()->at(rectKey))->getPosition().y + std::static_pointer_cast<RectangleComponent>(e->GetComponents()->at(rectKey))->getHeight() < yMidpoint);
//	
//	// check if entity fits in the bottom quadrants
//	bool bottomQuadrant = (std::static_pointer_cast<RectangleComponent>(e->GetComponents()->at(rectKey))->getPosition().y > yMidpoint);
//
//	// check if it fits in the left quadrants
//	if (std::static_pointer_cast<RectangleComponent>(e->GetComponents()->at(rectKey))->getPosition().x < xMidpoint
//		&& std::static_pointer_cast<RectangleComponent>(e->GetComponents()->at(rectKey))->getPosition().x + std::static_pointer_cast<RectangleComponent>(e->GetComponents()->at(rectKey))->getWidth() < xMidpoint)
//	{
//		if (topQuadrant == true)
//		{
//			index = 1;
//		}
//		else if (bottomQuadrant == true)
//		{
//			index = 2;
//		}
//	}
//	// check if it fits in the right quadrants
//	if (std::static_pointer_cast<RectangleComponent>(e->GetComponents()->at(rectKey))->getPosition().x > xMidpoint)
//	{
//		if (topQuadrant == true)
//		{
//			index = 0;
//		}
//		else if (bottomQuadrant == true)
//		{
//			index = 3;
//		}
//	}
//
//	return index;
//}
//
//void Quadtree::clear()
//{
//	// clear all entities
//	if (m_entities.empty() != true)
//	{
//		m_entities.clear();
//	}
//
//	// clears out each node
//	for (int i = 0; i < m_nodes.size(); i++)
//	{
//		if (m_nodes[i] != NULL) {
//			m_nodes[i]->clear();
//			m_nodes[i] = NULL;
//		}
//	}
//}