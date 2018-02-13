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
	void AddNode1(int ExistingNodeID, int NewNodeID);
	void AddNode2(int ExistingNodeID, int NewNodeID);
	void CreateRootNode(int NodeID);
	void MakeDecision(TreeNodes* node);

	bool SearchAddNode1(TreeNodes* CurrentNode, int ExistingNodeID, int NewNodeID);
	bool SearchAddNode2(TreeNodes* CurrentNode, int ExistingNodeID, int NewNodeID);

	TreeNodes* m_RootNode;

	DecisionTree();

	DecisionTree(int tarHp, int selfHP, int tarStr, int selfStr, int dist);
	

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

	int PHealth;
	int MHealth;
	int PStrength;
	int MStrength;
	int Distance;
};