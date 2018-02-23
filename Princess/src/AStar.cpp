#include "AStar.h"

AStar::AStar()
{
	currentDungeon = 0;
	graphSetUp = false;
}

Vec2f AStar::getPosition(Vec2f * target, Vec2f * targetNode)
{
	//get index of waypoint of target position and set it as start point for astar
	int startPoint = getWaypointIndex(*targetNode);
	Vec2f waypointPlayer = searchNearestWaypoint(*target);
	int endPoint = getWaypointIndex(waypointPlayer);
	Vec2f m_targetPosition = { 0,0 };

	if (startPoint != endPoint)
	{

		m_targetPosition = RunAStar(graph, &waypoints, &startPoint, &endPoint);

	}
	if (startPoint == endPoint)
	{
		m_targetPosition = *target;
	}
	return m_targetPosition;
}

Vec2f AStar::searchNearestWaypoint(Vec2f position)
{
	float differenceValue = std::numeric_limits<int>::max() - 10000;
	int differenceIndex;

	for (int i = 0; i < waypoints.size(); i++)
	{
		Vec2f difference;
		difference.x = position.x - waypoints.at(i).x;
		difference.y = position.y - waypoints.at(i).y;

		float diff = sqrtf((difference.x*difference.x) + (difference.y*difference.y));
		if (diff < differenceValue)
		{
			differenceValue = diff;
			differenceIndex = i;
		}
	}

	return waypoints.at(differenceIndex);
}

int AStar::getWaypointIndex(Vec2f pos)
{
	int index = 0;
	for (int i = 0; i < waypoints.size(); i++)
	{
		if (waypoints.at(i).x == pos.x && waypoints.at(i).y == pos.y)
		{
			index = i;
		}
	}
	return index;
}

Vec2f AStar::RunAStar(Graph<pair<string, int>, int>* graph, std::vector<Vec2f>* waypoints, int * start, int * end)
{
	std::vector<Node *> thepath;
	graph->aStar(graph->nodeArray()[*start], graph->nodeArray()[*end], thepath);//13 1
	for (int i = thepath.size() - 1; i > -1; i--)
	{
		//std::cout << "Location : " << thepath.at(i)->data().first << " Cost : " << thepath.at(i)->data().second << " h(n) : " << thepath.at(i)->getEstimatedDistToDest() << std::endl;
		if (thepath.at(i) == graph->nodeArray()[1])
		{
			std::cout << std::endl;
		}
	}

	string temp = thepath.at(thepath.size() - 2)->data().first;
	int tempInt = std::stoi(temp); // turn string into a int
	return waypoints->at(tempInt);
}

float AStar::getDistanceToDestination(Vec2f * currentPosition, Vec2f * targetPosition)
{
	float differenceValue = std::numeric_limits<int>::max() - 10000;
	int differenceIndex;

	Vec2f difference;
	difference.x = currentPosition->x - targetPosition->x;
	difference.y = currentPosition->y - targetPosition->y;

	float diff = sqrtf((difference.x*difference.x) + (difference.y*difference.y));

	return diff;
}

int AStar::getCurrentDungeon()
{
	return currentDungeon;
}

void AStar::setCurrentDungeon(int dungeon)
{
	currentDungeon = dungeon;

	if (currentDungeon == 1)
	{
		GraphSetUp("nodes.txt", "arcs.txt", 56);
	}
	else if (currentDungeon == 2)
	{
		GraphSetUp("nodes2.txt", "arcs2.txt", 18);
	}
	else if (currentDungeon == 3)
	{
		GraphSetUp("nodes3.txt", "arcs3.txt", 21);
	}
	else if (currentDungeon == 4)
	{
		GraphSetUp("nodes4.txt", "arcs4.txt", 38);
	}
	else if (currentDungeon == 5)
	{
		GraphSetUp("nodes5.txt", "arcs5.txt", 6);
	}
}

std::string AStar::getCurrentMapType()
{
	return mapType;
}

void AStar::setCurrentMapType(std::string type)
{
	mapType = type;
}

void AStar::GraphSetUp(std::string nodes, std::string arcs, int num)
{
	if (graphSetUp)
	{
		std::vector<Vec2f>::iterator it = waypoints.begin();
		while (it != waypoints.end())
		{
			it = waypoints.erase((it));
		}
		graph = NULL;
	}
	graph = new Graph<pair<string, int>, int>(num);
	std::string temp;
	int i = 0;
	ifstream myfile;
	float posX = 0;
	float posY = 0;
	myfile.open("AStarTextFiles/" + nodes);

	while (myfile >> temp >> posX >> posY)
	{
		graph->addNode(pair<string, int>(temp, std::numeric_limits<int>::max() - 10000), i);
		Vec2f waypoint = { posX, posY };
		waypoints.push_back(waypoint);
		i++;
	}
	myfile.close();

	myfile.open("AStarTextFiles/" + arcs);
	int from, to, weight;
	while (myfile >> from >> to >> weight)
	{
		graph->addArc(from, to, weight);
	}
	myfile.close();
	graphSetUp = true;
}