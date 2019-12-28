#include "Button.h"

Button::Button (float x, float y, float width, float height,
	sf::Font* font, std::string text, uint8_t characterSize,
	sf::Color textColor, sf::Color buttonColor)
{
	m_buttonState = BTN_IDLE;
	m_pressed = false;

	m_shape.setPosition(sf::Vector2f(x, y));
	m_shape.setSize(sf::Vector2f(width, height));
	m_shape.setFillColor(buttonColor);

	m_font = font;
	m_text.setFont(*m_font);
	m_text.setString(text);
	m_text.setFillColor(textColor);
	m_text.setCharacterSize(characterSize);
	m_text.setPosition(
		m_shape.getPosition().x + (m_shape.getGlobalBounds().width / 2.f) - m_text.getGlobalBounds().width / 2.f,
		m_shape.getPosition().y
	);
}


Button::~Button()
{
	
}

//Accesesors
const bool Button::isPressed() const
{
	if (m_buttonState == BTN_ACTIVE)
		return true;

	return false;
}

//Functions
void Button::update(const sf::Vector2i& mousePos)
{
	//Idle
	m_buttonState = BTN_IDLE;
	
	//Hover
	
	if(m_shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		//Active
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_buttonState = BTN_ACTIVE;
		}
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(m_shape);
	target->draw(m_text);
}
