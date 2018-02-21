#ifndef _SPRITECOMPONENT_H
#define _SPRITECOMPONENT_H

#include <iostream>

#include "Component.h"
class SpriteComponent : public Component
{
public:
	SpriteComponent(std::string sheetID, int layer, int noOfFrames, int sheetX, int sheetY, int width, int height, int direction)
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
		m_layer = layer;
		m_IsAnimating = true;
		m_relative = false;
	}
	~SpriteComponent() {};

	void Direction(int dir) { m_direction = dir; };
	int Direction() { return m_direction; };

	void Frame(int frame) {
		if (frame < 0)
		{
			frame = m_noOfFrames;
		}
		else if (frame > m_noOfFrames)
		{
			frame = 0;
		}
		m_frame = frame;
	};
	int Frame() { return m_frame; };

	void Width(int width) { m_width = width; };
	int Width() { return m_width; };

	void Height(int height) { m_height = height; };
	int Height() { return m_height; };

	void Layer(int x) { m_layer = x; };
	int Layer() { return m_layer; }

	void Sheet(std::string x) { m_sheetID = x; };
	std::string Sheet() { return m_sheetID; };

	void SheetX(int x) { m_sheetX = x; };
	int SheetX() { return m_sheetX; };

	void SheetY(int y) { m_sheetY = y; };
	int SheetY() { return m_sheetY; };

	void IsAnimating(bool Animating) { m_IsAnimating = Animating; };
	bool IsAnimating() { return m_IsAnimating; };

	void Relative(bool x) { m_relative = x; };
	bool Relative() { return m_relative; };

	SDL_Rect GetRect() { return SDL_Rect{ ((m_sheetX + (m_sheetX* m_noOfFrames)) + m_frame) * m_width, ((m_sheetY * 4) + m_direction) * m_height, m_width, m_height }; }

private:

	int m_sheetX, m_sheetY;
	int m_noOfFrames;
	int m_frame;
	int m_width, m_height;
	int m_direction; // 0 Up, 1 Down, 2 Left, 3 Right
	int m_layer;
	std::string m_sheetID;
	bool m_IsAnimating;
	bool m_relative;
};
#endif
