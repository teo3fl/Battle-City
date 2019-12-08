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

enum Button_States
{
	BTN_IDLE = 0,
	BTN_HOVER,
	BTN_ACTIVE

};

class Button
{
public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, 
		sf::Color idleColor, sf::Color m_hoverColor, sf::Color m_activeColor);
	virtual ~Button();

	//Accessors
	const bool isPressed() const;

	//Functions
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget* target);

private:
	bool m_pressed;
	bool m_hover;
	short unsigned m_buttonState; 

    sf::RectangleShape m_shape;
	sf::Font* m_font;
	sf::Text m_text;

	sf::Color m_idleColor;
	sf::Color m_hoverColor;
	sf::Color m_activeColor;



};

#endif
