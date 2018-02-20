#include "TreeNodes.h"

TreeNodes::TreeNodes()
{
	NewBranch1 = nullptr;
	NewBranch2 = nullptr;

	m_NodeID = 0;
}

//deconstructor
TreeNodes::~TreeNodes()
{ }


TreeNodes::TreeNodes(int nodeID)
{
	//create tree node with a specific node ID
	m_NodeID = nodeID;

	//reset nodes
	NewBranch1 = nullptr;
	NewBranch2 = nullptr;
}


void TreeNodes::setMarked(bool state)
{
	m_marked = state;
}

bool TreeNodes::getMarked()
{
	return m_marked;
}

void TreeNodes::setEnd(bool state)
{
	m_end = state;
}

bool TreeNodes::getEnd()
{
	return m_end;
}