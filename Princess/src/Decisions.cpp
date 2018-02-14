//destructor
//Final Step in a sense
#include "DecisionTree.h"
using namespace std;
#include <iostream>
DecisionTree::~DecisionTree()
{
	RemoveNode(m_RootNode);
}

//Step 2!
void DecisionTree::CreateRootNode(int NodeID)
{
	//create root node with specific ID
	// In MO, you may want to use thestatic creation of IDs like with entities. depends on how many nodes you plan to have
	//or have instantaneously created nodes/changing nodes
	m_RootNode = new TreeNodes(NodeID);
}

//Step 5.1!~
void DecisionTree::AddNode1(int ExistingNodeID, int NewNodeID)
{
	//check to make sure you have a root node. can't add another node without a root node
	if (m_RootNode == nullptr)
	{
		std::cout << "ERROR - No Root Node" << std::endl;
		return;
	}

	if (SearchAddNode1(m_RootNode, ExistingNodeID, NewNodeID))
	{
		cout << "Added Node Type1 With ID " << NewNodeID << " onto Branch Level " << ExistingNodeID << endl;
	}
	else
	{
		//check
		cout << "Node: " << ExistingNodeID << " Not Found." << std::endl;
	}
}