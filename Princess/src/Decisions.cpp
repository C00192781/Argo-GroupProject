#include <iostream>
#include <random>
#include "DecisionTree.h"
#include <ctime>
int random(int upperLimit);

//rand func
int random(int upperLimit)
{
	int randNum = rand() % upperLimit;
	return randNum;
}

DecisionTree::DecisionTree()
{
	//set root node to null
	m_RootNode = NULL;
}

DecisionTree::DecisionTree(int tarHp, int selfHP, int tarStr, int selfStr, int dist, int range, int eRange) //overload with ai params
{
	m_RootNode = NULL;

	PHealth = tarHp;
	MHealth = selfHP;
	PStrength = tarStr;
	MStrength = selfStr;
	Distance = dist;
	Range = range;
	EnemyRange = eRange;
}

//destructor
DecisionTree::~DecisionTree()
{
	RemoveNode(m_RootNode);
}

void DecisionTree::CreateRootNode(int NodeID)
{
	//create root
	m_RootNode = new TreeNodes(NodeID);
	m_Size++;
}


void DecisionTree::AddNode1(TreeNodes* base, int ExistingNodeID, int NewNodeID)
{
	//check to make sure you have a root node. can't add another node without a root node
	if (m_RootNode == NULL)
	{
		cout << "ERROR - No Root Node";
		return;
	}

	if (SearchAddNodesOn(base, ExistingNodeID, NewNodeID))
	{
		cout << "Added Node Type1 With ID " << NewNodeID << " onto Branch Level " << ExistingNodeID << endl;
	}
	else
	{
		//check
		/*cout << "Node: " << ExistingNodeID << " Not Found.";*/
	}

	m_Size++;
}


// function to print leaf 
// nodes from left to right
int DecisionTree::calculatePathNodes(TreeNodes* root, int dist, int tarHP, int selfHp, int range, int enemyRange) //this perfectly searches the tree in order  1 2 4 5 1 3 6 7!
{
	PHealth = tarHP;
	MHealth = selfHp;
	Distance = dist;
	Range = range;
	EnemyRange = enemyRange;


	// if node is null, return
	if (!root)
	{
	//	return root->m_NodeID;
	}

	
	bool decision = MakeDecision(root); //try to make a decision at current node

	//cout << "DECIDE SOMETHING AT " << root->m_NodeID << " " << endl;

	// if node is leaf node, print its data    
	if (!root->NewBranch1 && !root->NewBranch2)
	{
	//	cout << "leaf: " << root->m_NodeID << endl;

		m_decision = root->m_NodeID;
	}

	// if left child exists, check for leaf 
	// recursively
	if (root->NewBranch1 && decision) //if option one, go left
	{
	//	cout << "go left at " << root->m_NodeID << endl;
		calculatePathNodes(root->NewBranch1, dist, tarHP, selfHp, Range, EnemyRange);
	}

	// if right child exists, check for leaf 
	// recursively
	if (root->NewBranch2 && !decision) //if option 2, go right
	{
	//	cout << "go right at " << root->m_NodeID << endl;
		calculatePathNodes(root->NewBranch2, dist, tarHP, selfHp, Range, EnemyRange);
	}

	return root->m_NodeID;
}



bool DecisionTree::searchNodes(TreeNodes* currentNode, int ExistingNodeID, int NewNodeID) //this perfectly searches the tree in order  1 2 4 5 1 3 6 7!
{


	if (currentNode->NewBranch1) //if option one, go left
	{
		cout << "go left at " << currentNode->m_NodeID << endl;

		SearchAddNodesOn(currentNode->NewBranch1, ExistingNodeID, NewNodeID);
	}

	// if right child exists, check for leaf 
	// recursively
	if (currentNode->NewBranch2) //if option 2, go right
	{
		cout << "go right at " << currentNode->m_NodeID << endl;

		SearchAddNodesOn(currentNode->NewBranch2, ExistingNodeID, NewNodeID);
	}

	if (currentNode->m_NodeID == NewNodeID) //get outta here when we're done
	{
		return true;
	}
	else
	{
		if (currentNode->m_NodeID % 2 == 0)
		{
			searchNodes(currentNode->NewBranch1, ExistingNodeID, NewNodeID); //check left branch node next
		}
		else
		{
			searchNodes(currentNode->NewBranch2, ExistingNodeID, NewNodeID); //right branch node next
		}
	}


}

int DecisionTree::getDecision()
{
	return m_decision;
}

// function to search 
// nodes from left to right
bool DecisionTree::SearchAddNodesOn(TreeNodes* CurrentNode, int ExistingNodeID, int NewNodeID) //this searches the tree in order  1 2 4 5 1 3 6 7 etc etc L->R
{
	m_RootNode;


	if (CurrentNode->m_NodeID == NewNodeID) //end it all when the current node ID is the added node.
	{
		return false; 
	}

	// if node is null, return
	if (!CurrentNode)
	{
		return false;
	}


// if node is leaf node, print its data    
	if (!CurrentNode->NewBranch1)// && CurrentNode->m_NodeID == ExistingNodeID) 
	{
		if (!CurrentNode->NewBranch1 && NewNodeID % 2 == 0) //
		{
			CurrentNode->NewBranch1 = new TreeNodes(NewNodeID);
			SearchAddNodesOn(CurrentNode->NewBranch1, ExistingNodeID, NewNodeID);
			//add left node
		}

		return true;
	}

	if (!CurrentNode->NewBranch2)// && CurrentNode->m_NodeID == ExistingNodeID)
	{
		if (!CurrentNode->NewBranch2 && NewNodeID % 2 != 0)
		{
			CurrentNode->NewBranch2 = new TreeNodes(NewNodeID);
			SearchAddNodesOn(CurrentNode->NewBranch2, ExistingNodeID, NewNodeID);
			//add right node
		}

	}

	if (CurrentNode->m_NodeID % 2 == 0)
	{
		SearchAddNodesOn(CurrentNode->NewBranch1, ExistingNodeID, NewNodeID); //check left branch node next
	}
	else
	{
		SearchAddNodesOn(CurrentNode->NewBranch2, ExistingNodeID, NewNodeID); //right branch node next
	}

}


void DecisionTree::QueryTree(TreeNodes* CurrentNode)
{
	if (CurrentNode->NewBranch1 == NULL) 
	{
		cout << "Missing Branch 1";
	}
	if (CurrentNode->NewBranch2 == NULL)
	{
		cout << "Missing Branch 2";
		return;
	}

	// test decisions at current node
	MakeDecision(CurrentNode);
}


void DecisionTree::Query()
{
	QueryTree(m_RootNode);
}

//make decisions with passed ai params
bool DecisionTree::MakeDecision(TreeNodes *node)
{

	srand(time(NULL));


	if (node->m_NodeID == 1) //MAKE DECISIONS AND NODE PATHING HERE
	{

		//if statement lower/higher query respective branch
		if (PHealth < MHealth)
		{
		//	cout << "mon adv hp " << endl;
			return true;
		}
		else
		{
		//	cout << "no hp adv " << endl;
			return false;
		}
	}

	else if (node->m_NodeID == 2)
	{
		if (Distance < Range) //if in range, atk //FEED IN ACTUAL WEAPON MAX_RANGE TO THIS THING pls
		{
			//cout << "mon adv str " << endl;
			return true;
		}
		else //else seek
		{
		//	cout << "no str adv " << endl;
			return false;
		}
	}


	else if (node->m_NodeID == 3)
	{
		if (Distance > EnemyRange) //if in range flee
		{
			//cout << "mon adv str " << endl;
			return true;
		}
		else //else chill
		{

			//	cout << "no str adv " << endl;
			return false;
		}
	}




	
}

void DecisionTree::Output()
{
	//display
	DisplayTree(m_RootNode);
}

void DecisionTree::DisplayTree(TreeNodes* CurrentNode)
{
	//doesn't exist, don't display
	if (CurrentNode == NULL)
	{
		return;
	}

	cout << "Node ID " << CurrentNode->m_NodeID << "Decision Display: " << endl;

	//go branch 1
	DisplayTree(CurrentNode->NewBranch1);

	//go branch 2
	DisplayTree(CurrentNode->NewBranch2);
}

void DecisionTree::RemoveNode(TreeNodes *node)
{
	if (node != NULL)
	{
		if (node->NewBranch1 != NULL)
		{
			RemoveNode(node->NewBranch1);
		}

		if (node->NewBranch2 != NULL)
		{
			RemoveNode(node->NewBranch2);
		}

		cout << "Deleting Node" << node->m_NodeID << endl;

		//delete node
		delete node;
		//reset node
		node = NULL;
	}
}