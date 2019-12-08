#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include "SFMl/System.hpp"
#include "SFMl/Window.hpp"
#include "SFMl/Graphics.hpp"
#include "SFMl/Audio.hpp"


class Button
{
private:
	sf::RectangleShape m_shape;
	sf::Font* m_font;
	sf::Text m_text;

	sf::Color m_idleColor;
	sf::Color m_hoverColor;
	sf::Color m_activeColor;

	
	
public:
	Button();
	virtual ~Button();
};

#endif
