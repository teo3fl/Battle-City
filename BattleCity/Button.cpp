#include "Button.h"

Button::Button(float x, float y, float width, float height, 
	sf::Font* font, std::string text, 
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	m_shape.setPosition(sf::Vector2f(x, y));
	m_shape.setSize(sf::Vector2f(width, height));
	m_font = font;
	m_text.setFont(*this->m_font);
	m_text.setString(text);
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(12);
	m_text.setPosition(
		m_shape.getPosition().x / 2.f - m_text.getGlobalBounds().width / 2.f,
	    m_shape.getPosition().y / 2.f - m_text.getGlobalBounds().height / 2.f
	);
	
	m_idleColor = idleColor;
	m_hoverColor = hoverColor;
	m_activeColor = activeColor;

	m_shape.setFillColor(m_idleColor);
}

Button::~Button()
{
	
}

void Button::update(const sf::Vector2f& mousePos)
{
	/*Update the booleans for hover and pressed*/

	//Hover
	if(m_shape.getGlobalBounds().contains(mousePos))
	{
		
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(m_shape);
}
