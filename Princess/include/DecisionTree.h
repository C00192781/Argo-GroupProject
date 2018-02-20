//the decision tree class
#include "TreeNodes.h"
class DecisionTree
{
public:
	//functions
	void RemoveNode(TreeNodes* node);
	void DisplayTree(TreeNodes* CurrentNode);
	void Output();
	void Query();
	void QueryTree(TreeNodes* rootNode);
	void AddNode1(TreeNodes* base, int ExistingNodeID, int NewNodeID);
	void CreateRootNode(int NodeID);
	bool MakeDecision(TreeNodes* node);

	int getDecision();
	bool SearchAddNodesOn(TreeNodes* CurrentNode, int ExistingNodeID, int NewNodeID); //this perfectly searches the tree in order  1 2 4 5 1 3 6 7!
	TreeNodes* m_RootNode;
	bool searchNodes(TreeNodes* currentNode, int ExistingNodeID, int NewNodeID);
	DecisionTree();

	DecisionTree(int tarHp, int selfHP, int tarStr, int selfStr, int dist, int range, int eRange);
	int calculatePathNodes(TreeNodes* root, int dist, int tarHP, int selfHp, int range, int eRange);

	TreeNodes* m_lastNode;

		////PHealth = random(60);
		////MHealth = random(60);
		////PStrength = random(50);
		////MStrength = random(50);
		////DistanceFBase = random(75);
		////DistanceFMonster = random(75);
	 ~DecisionTree();


private: 
	int m_Size = 0;
	int m_decision = 0;

	int PHealth;
	int MHealth;
	int PStrength;
	int MStrength;
	int Distance;

	int Range;
	int EnemyRange;

	int test1;
	int test2;
	int test3;
};