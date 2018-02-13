using namespace std;
//tree node class
class TreeNodes
{
public:
	//tree node functions
	TreeNodes(int nodeID);
	TreeNodes();

	virtual ~TreeNodes();

	int m_NodeID;

	TreeNodes* NewBranch1;
	TreeNodes* NewBranch2;

	void setMarked(bool state);
	bool getMarked();

	void setEnd(bool state);
	bool getEnd();


	bool m_marked = false;

	bool m_end = false;

};