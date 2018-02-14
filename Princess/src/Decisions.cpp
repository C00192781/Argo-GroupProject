#include <iostream>
#include <random>
#include "DecisionTree.h"
#include <ctime>
int random(int upperLimit);

//for random variables that will effect decisions/node values/weights
int random(int upperLimit)
{
	int randNum = rand() % upperLimit;
	return randNum;
}

//constructor
//Step 1!
DecisionTree::DecisionTree()
{
	//set root node to null on tree creation
	//beginning of tree creation
	m_RootNode = NULL;
}

DecisionTree::DecisionTree(int tarHp, int selfHP, int tarStr, int selfStr, int dist)
{
	m_RootNode = NULL;

	PHealth = tarHp;
	MHealth = selfHP;
	PStrength = tarStr;
	MStrength = selfStr;
	Distance = dist;
}

//destructor
//Final Step in a sense
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
	m_Size++;
}

//Step 5.1!~
void DecisionTree::AddNode1(TreeNodes* base, int ExistingNodeID, int NewNodeID)
{
	//check to make sure you have a root node. can't add another node without a root node
	if (m_RootNode == NULL)
	{
		cout << "ERROR - No Root Node";
		return;
	}

	if (SearchAddJank1(base, ExistingNodeID, NewNodeID))
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
void DecisionTree::printLeafNodes(TreeNodes* root) //this perfectly searches the tree in order  1 2 4 5 1 3 6 7!
{
	// if node is null, return
	if (!root)
	{
		return;
	}

	
	bool decision = MakeDecision(root); //try to make a decision at each node. NOTE: we only want to make decisions at the nodes we walk through ultimately! this tests every node!
	//cout << "DECIDE SOMETHING AT " << root->m_NodeID << " " << endl;

	// if node is leaf node, print its data    
	if (!root->NewBranch1 && !root->NewBranch2)
	{
	//	cout << "leaf: " << root->m_NodeID << endl;

		return;
	}

	// if left child exists, check for leaf 
	// recursively
	if (root->NewBranch1 && decision) //if option one, go left
	{
		cout << "go left at " << root->m_NodeID << endl;
		printLeafNodes(root->NewBranch1);
	}

	// if right child exists, check for leaf 
	// recursively
	if (root->NewBranch2 && !decision) //if option 2, go right
	{
		cout << "go right at " << root->m_NodeID << endl;
		printLeafNodes(root->NewBranch2);
	}
}


//Step 6.1!~ search and add new node to current node
bool DecisionTree::SearchAddNode1(TreeNodes *CurrentNode, int ExistingNodeID, int NewNodeID)
{

	//if there is a node
	if (CurrentNode->m_NodeID == ExistingNodeID)
	{
		//create the node
		if (CurrentNode->NewBranch1 == NULL)
		{
			CurrentNode->NewBranch1 = new TreeNodes(NewNodeID);
		}
		else
		{
			CurrentNode->NewBranch1 = new TreeNodes(NewNodeID);
		}
		return true;
	}
	else
	{
		//try branch if it exists
		//for a third, add another one of these too!
		if (CurrentNode->NewBranch1 != NULL)
		{
			if (SearchAddNode1(CurrentNode->NewBranch1, ExistingNodeID, NewNodeID))
			{
		//		m_lastNode = CurrentNode;
				return true;
			}
			else
			{
				//try second branch if it exists
				if (CurrentNode->NewBranch2 != NULL)
				{
					m_lastNode = CurrentNode;
					return(SearchAddNode2(CurrentNode->NewBranch2, ExistingNodeID, NewNodeID));
				}
				else
				{
			//		m_lastNode = CurrentNode;
					return false;
				}
			}
		}
	//	m_lastNode = CurrentNode;
		CurrentNode->setEnd(true);



		return(SearchAddNode1(m_RootNode->NewBranch2, ExistingNodeID, NewNodeID)); //this is janky for dynamic tree size 



		//return false;
	}
	return false;
}

bool DecisionTree::searchNodes(TreeNodes* currentNode, int ExistingNodeID, int NewNodeID) //this perfectly searches the tree in order  1 2 4 5 1 3 6 7!
{
	//// if node is null, return
	//if (!currentNode)
	//{
	//	return false;
	//}

	//									// if node is leaf node, print its data   


	//if (!currentNode->NewBranch1 && !currentNode->NewBranch2)
	//{
	//	//	cout << "leaf: " << currentNode->m_NodeID << endl;

	////	return false;
	//}

	// if left child exists, check for leaf 
	// recursively


	

	if (currentNode->NewBranch1) //if option one, go left
	{
		cout << "go left at " << currentNode->m_NodeID << endl;

		SearchAddJank1(currentNode->NewBranch1, ExistingNodeID, NewNodeID);
	}

	// if right child exists, check for leaf 
	// recursively
	if (currentNode->NewBranch2) //if option 2, go right
	{
		cout << "go right at " << currentNode->m_NodeID << endl;

		SearchAddJank1(currentNode->NewBranch2, ExistingNodeID, NewNodeID);
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



// function to print leaf 
// nodes from left to right
bool DecisionTree::SearchAddJank1(TreeNodes* CurrentNode, int ExistingNodeID, int NewNodeID) //this perfectly searches the tree in order  1 2 4 5 1 3 6 7!
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

	//if (CurrentNode->NewBranch1 == NULL)
	//{
	//	CurrentNode->NewBranch1 = new TreeNodes(NewNodeID);
	//}
	//else
	//{
	//	CurrentNode->NewBranch1 = new TreeNodes(NewNodeID);
	//}

// if node is leaf node, print its data    

	if (!CurrentNode->NewBranch1)// && CurrentNode->m_NodeID == ExistingNodeID) 
	{
		if (!CurrentNode->NewBranch1 && NewNodeID % 2 == 0) //
		{
			CurrentNode->NewBranch1 = new TreeNodes(NewNodeID);
			SearchAddJank1(CurrentNode->NewBranch1, ExistingNodeID, NewNodeID);
			//add left node
		}
	
	/*	else
		{
			cout << "well that was unexpected" << endl;
		}*/

		return true;
	}

	if (!CurrentNode->NewBranch2)// && CurrentNode->m_NodeID == ExistingNodeID)
	{
		if (!CurrentNode->NewBranch2 && NewNodeID % 2 != 0)
		{
			CurrentNode->NewBranch2 = new TreeNodes(NewNodeID);
			SearchAddJank1(CurrentNode->NewBranch2, ExistingNodeID, NewNodeID);
			//add right node
		}

		//else
		//{
		//	cout << "well that was unexpected" << endl;
		//}

	}

	if (CurrentNode->m_NodeID % 2 == 0)
	{
		SearchAddJank1(CurrentNode->NewBranch1, ExistingNodeID, NewNodeID); //check left branch node next
	}
	else
	{
		SearchAddJank1(CurrentNode->NewBranch2, ExistingNodeID, NewNodeID); //right branch node next
	}

}


////Step 6.1!~ search and add new node to current node
//bool DecisionTree::SearchAddNode1(TreeNodes *CurrentNode, int ExistingNodeID, int NewNodeID)
//{
//	if (CurrentNode->m_NodeID == 3)
//	{
//		int q = 5;
//		q -= 5;
//	}
//
//	if (m_RootNode->m_NodeID != 1)
//	{
//		int qq = 5;
//		qq -= 5;
//	}
//
////if a node exists
//	if (CurrentNode->m_NodeID == ExistingNodeID)
//	{
//		//create the node
//		if (CurrentNode->NewBranch1 == NULL)
//		{
//			CurrentNode->NewBranch1 = new TreeNodes(NewNodeID);
//		}
//		else
//		{
//			CurrentNode->NewBranch1 = new TreeNodes(NewNodeID);
//		}
//		return true;
//	}
//	else
//	{
//		//try branch if it exists
//		//for a third, add another one of these too!
//		if (CurrentNode->NewBranch1 != NULL)
//		{
//			if (SearchAddNode1(CurrentNode->NewBranch1, ExistingNodeID, NewNodeID)) // we got in here
//			{
//				return true;
//			}
//			else
//			{
//				//try second branch if it exists
//				if (CurrentNode->NewBranch2 != NULL)
//				{
//					CurrentNode->setMarked(true);
//					
//
//					return(SearchAddNode2(CurrentNode->NewBranch2, ExistingNodeID, NewNodeID));
//				}
//				else
//				{
//					if (CurrentNode->m_NodeID != 7) //temp test
//					{
//						
//						return(SearchAddNode2(CurrentNode->NewBranch2, ExistingNodeID, NewNodeID));
//					}
//					//return false;
//				}
//			}
//		}
//
//		if (CurrentNode->getEnd())
//		{
//			return false;
//		}
//		
//	}
//}

//Step 5.2!~    does same thing as node 1.  if you wanted to have more decisions, 
//create a node 3 which would be the same as this maybe with small differences
void DecisionTree::AddNode2(int ExistingNodeID, int NewNodeID)
{
	if (m_RootNode == NULL)
	{
		cout << "ERROR - No Root Node";
	}

	if (SearchAddNode2(m_RootNode, ExistingNodeID, NewNodeID))
	{
	//	cout << "Added Node Type2 With ID " << NewNodeID << " onto Branch Level " << ExistingNodeID << endl;
	}
	else
	{
		cout << "Node: " << ExistingNodeID << " Not Found.";
	}
	m_Size++;
}

//Step 6.2!~ search and add new node to current node
//as stated earlier, make one for 3rd node if there was meant to be one
bool DecisionTree::SearchAddNode2(TreeNodes *CurrentNode, int ExistingNodeID, int NewNodeID)
{
	if (CurrentNode->m_NodeID == ExistingNodeID)
	{
		//create the node
		if (CurrentNode->NewBranch2 == NULL)
		{
			CurrentNode->NewBranch2 = new TreeNodes(NewNodeID);
		}
		else
		{
			CurrentNode->NewBranch2 = new TreeNodes(NewNodeID);
		}
		return true;
	}
	else
	{
		//try branch if it exists
		if (CurrentNode->NewBranch1 != NULL)
		{
			if (SearchAddNode2(CurrentNode->NewBranch1, ExistingNodeID, NewNodeID))
			{
				return true;
			}
			else
			{
				//try second branch if it exists
				if (CurrentNode->NewBranch2 != NULL)
				{
					return(SearchAddNode2(CurrentNode->NewBranch2, ExistingNodeID, NewNodeID));
				}
				else
				{
					return false;
				}
			}
		}
		return false;
	}
}

//Step 11
void DecisionTree::QueryTree(TreeNodes* CurrentNode)
{
	if (CurrentNode->NewBranch1 == NULL) //this only visits first node decision, it should be eating more big ol decisions.
	{
		//if both branches are null, tree is at a decision outcome state
		if (CurrentNode->NewBranch2 == NULL)
		{
			//output decision 'question'
			///////////////////////////////////////////////////////////////////////////////////////
		}
		else
		{
			cout << "Missing Branch 1";
		}
		return;
	}
	if (CurrentNode->NewBranch2 == NULL)
	{
		cout << "Missing Branch 2";
		return;
	}

	//otherwise test decisions at current node
	MakeDecision(CurrentNode);
}

//Step 10
void DecisionTree::Query()
{
	QueryTree(m_RootNode);
}

////////////////////////////////////////////////////////////
//debate decisions   create new function for decision logic

// cout << node->stringforquestion;

//Step 12
bool DecisionTree::MakeDecision(TreeNodes *node)
{
	//should I declare variables here or inside of decisions.h


	////sets random!
	srand(time(NULL));

	//randomly create the numbers for health, strength and distance for each variable
	////PHealth = random(60);
	////MHealth = random(60);
	////PStrength = random(50);
	////MStrength = random(50);
	////DistanceFBase = random(75);
	////DistanceFMonster = random(75);

	//the decision to be made string example: Player health: Monster Health:  player health is lower/higher
	//cout << "Player Health: " << PHealth << endl;
	//cout << "Monster Health: " << MHealth << endl;
	//cout << "Player Strength: " << PStrength << endl;
	//cout << "Monster Strength: " << MStrength << endl;
	//cout << "Distance between: " << Distance << endl;

	//MH > PH
	//MH < PH
	//PS > MS
	//PS > MS
	//DB > DM
	//DB < DM

	//good place to break off into different decision nodes, not just 'binary'


	if (node->m_NodeID == 1)
	{

		//if statement lower/higher query respective branch
		if (PHealth > MHealth)
		{
			cout << "mon adv hp " << endl;
			return true;
		}
		else
		{
			cout << "no hp adv " << endl;
			return false;
		}
	}


	else if (node->m_NodeID == 2)
	{
		if (PStrength < MStrength)
		{
			cout << "mon adv str " << endl;
			return true;
		}
		else
		{

			cout << "no str adv " << endl;
			return false;
		}
	}
	//re-do question for next branch. Player strength: Monster strength: Player strength is lower/higher
	//if statement lower/higher query respective branch

	else if (node->m_NodeID == 4)
	{
		if (Distance < 60)
		{
			cout << "in range " << endl;
			return true;
		}
		else
		{
			cout << "out of range" << endl;
			return false;
		}
	}

	//recursive question for next branch. Player distance from base/monster. 
	else if (node->m_NodeID == 5)
	{
		if (Distance < 60)
		{
			cout << "distance case 2 close " << endl;
			return true;
		}
		else
		{
			cout << "distance case 3 far" << endl;
			return false;
		}
	}

	else if (node->m_NodeID == 3)
	{
		if (test1 < 1)
		{
			cout << "test 1 confirmed " << endl;
			return true;
		}
		else
		{
			cout << "test 1 false " << endl;
			return false;
		}
	}


	else if (node->m_NodeID == 6)
	{
		if (test2 < 1)
		{
			cout << "test 2 confirmed " << endl;
			return true;
		}
		else
		{
			cout << "test 2 false " << endl;
			return false;
		}
	}


	else if (node->m_NodeID == 7)
	{
		if (test3 < 1)
		{
			cout << "test 3 confirmed " << endl;
			return true;
		}
		else
		{
			cout << "test 3 false " << endl;
			return false;
		}
	}

	//default CASE?



	//DECISION WOULD BE MADE
	//if statement?
	// inside query output decision?
	//cout <<  << 

	////QueryTree(node->NewBranch2);

	////MakeDecision(node);
	/// 
}

//Step.....8ish?
void DecisionTree::Output()
{
	//take repsective node
	DisplayTree(m_RootNode);
}

//Step 9
void DecisionTree::DisplayTree(TreeNodes* CurrentNode)
{
	//if it doesn't exist, don't display of course
	if (CurrentNode == NULL)
	{
		return;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//need to make a string to display for each branch
	cout << "Node ID " << CurrentNode->m_NodeID << "Decision Display: " << endl;

	//go down branch 1
	DisplayTree(CurrentNode->NewBranch1);

	//go down branch 2
	DisplayTree(CurrentNode->NewBranch2);
}

//Final step at least in this case. A way to Delete node from tree. Can't think of a way to use it yet but i know it's needed
void DecisionTree::RemoveNode(TreeNodes *node)
{
	//could probably even make it to where you delete a specific node by using it's ID
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

		//delete node from memory
		delete node;
		//reset node
		node = NULL;
	}
}