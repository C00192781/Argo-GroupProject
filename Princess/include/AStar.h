#pragma once
#include "Graph.h"
#include <fstream>
#include <string>
#include <iostream>

struct Vec2f
{
	float x;
	float y;
};

class AStar
{
public:
	AStar();
	void GraphSetUp(std::string nodes, std::string arcs, int num);
	Vec2f getPosition(Vec2f * target, Vec2f * targetNode);

	Vec2f searchNearestWaypoint(Vec2f playerPos);
	int getWaypointIndex(Vec2f pos);
	Vec2f RunAStar(Graph<pair<string, int>, int>* graph, std::vector<Vec2f>* waypoints, int *start, int *end);

	float getDistanceToDestination(Vec2f * currentPosition, Vec2f * targetPosition);
	int getCurrentDungeon();
	void setCurrentDungeon(int dungeon);
	std::string getCurrentMapType();
	void setCurrentMapType(std::string type);


private:
	// AStar + Graph
	typedef GraphArc<string, int> Arc;
	typedef GraphNode<pair<string, int>, int> Node;
	Graph<pair<string, int>, int>* graph;
	std::vector<Vec2f> waypoints;
	int currentDungeon;
	std::string mapType;

	bool graphSetUp;
};