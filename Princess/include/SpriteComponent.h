#ifndef _SPRITECOMPONENT_H
#define _SPRITECOMPONENT_H

#include "Component.h"
class SpriteComponent : public Component
{
public:
	SpriteComponent(std::string sheetID, int noOfFrames, int sheetX, int sheetY, int width, int height, int direction)
	{
		m_sheetID = sheetID;
		m_noOfFrames = noOfFrames;
		m_sheetX = sheetX;
		m_sheetY = sheetY;
		m_width = width;
		m_height = height;
		m_direction = direction;
		m_type = "SC";
		m_frame = 0;
	 }
	~SpriteComponent() {};

	void Direction(int dir) { m_direction = dir; };
	int Direction(){ return m_direction; };

	void Frame(int frame) { 
		if (frame < 0)
		{
			frame = m_noOfFrames;
		}
		else if( frame > m_noOfFrames)
		{
			frame = 0;
		}
		m_frame = frame; 
	};
	int Frame() { return m_frame; };

	void Width(int width) {m_width = width; };
	int Width() { return m_width; };

	void Height(int height) { m_height = height; };
	int Height() { return m_height; };

	std::string Sheet() { return m_sheetID; };

	SDL_Rect GetRect() {
		return SDL_Rect{ ((m_sheetX * m_noOfFrames) + m_frame) * m_width, ((m_sheetY * 4) + m_direction) * m_height, m_width, m_height };}

private:

	int m_sheetX, m_sheetY;
	int m_noOfFrames;
	int m_frame;
	int m_width, m_height;
	int m_direction; // 0 Up, 1 Down, 2 Left, 3 Right
	std::string m_sheetID;

};
#endif

