#include "Quad.h"



Quad::Quad(int width, int height, int depth)
{
	m_width = width;
	m_height = height;
	m_depth = depth;
	int squares = 4;
	for (int i = 0; i < m_depth; i++)
	{
		squares *= squares;
	}
	m_dimensions = sqrt(squares);
	int tempWidth = width / m_dimensions;
	int tempHeight = height / m_dimensions;
}


Quad::~Quad()
{
}


void Quad::Fission(std::vector<Entity*>* entities)
{
	int tempWidth = m_width / m_dimensions;
	int tempHeight = m_height / m_dimensions;
	m_entities.clear();
	for (int i = 0; i < m_dimensions; i++)
	{
		std::vector<std::vector<Entity*>> temp;
		for (int j = 0; j < m_dimensions; j++)
		{
			std::vector<Entity*> temp2;
			temp.push_back(temp2);
		}
		m_entities.push_back(temp);
	}
	for (int i = 0; i < entities->size(); i++)
	{
		PositionComponent* position = new PositionComponent();
		for (int j = 0; j < entities->at(i)->GetComponents()->size(); j++)
		{
			if (entities->at(i)->GetComponents()->at(j)->Type() == "PC")
			{
				delete position;
				position = static_cast<PositionComponent*>(entities->at(i)->GetComponents()->at(j));
				break;
			}
		}
		int x = (int)position->getPosition().x / tempWidth;
		int y = (int)position->getPosition().y / tempHeight;
		m_entities.at(x).at(y).push_back(entities->at(i));
	}
	int x = 9999;
	timeUp++;
	std::cout << "INTO INFINITY WE GO! " << timeUp << std::endl;
}
