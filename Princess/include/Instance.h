#ifndef _INSTANCE_H
#define _INSTANCE_H

#include <string>

class Instance
{
public:
	Instance() {};
	~Instance() {};

	virtual void Update() = 0;
	virtual void Render() = 0;

	std::string ID() { return m_id; };

private:

	std::string m_id;

};

#endif
