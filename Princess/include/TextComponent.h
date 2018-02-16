#ifndef _TEXTCOMPONENT_H
#define _TEXTCOMPONENT_H

#include <iostream>

#include "Component.h"
class TextComponent : public Component
{
public:
	TextComponent(std::string fontID, std::string text, SDL_Color c, int width, int height)
	{
		m_color = c;
		m_width = width;
		m_height = height;
		m_fontID = fontID;
		m_text = text;
		m_type = "TextComponent";
	}
	~TextComponent() {};

	std::string FontID() { return m_fontID; };
	void FontID(std::string x) { m_fontID = x; };

	std::string Text() { return m_text; };
	void Text(std::string x) { m_text = x; };

	SDL_Color Color() { return m_color; };
	void Color(SDL_Color col) { m_color = col; };

	int Width() { return m_width; };
	void Width(int x) { m_width = x; };

	int Height() { return m_height; };
	void Height(int x) { m_height = x; };


private:

	std::string m_fontID, m_text;
	SDL_Color m_color;
	int m_width, m_height;

};
#endif
