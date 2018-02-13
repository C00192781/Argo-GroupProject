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

	virtual ~DecisionTree();
};	