#ifndef BUTTON_H
#define BUTTON_H

enum Button_States
{
	BTN_IDLE = 0,
	BTN_ACTIVE

};

class Button
{
public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, uint8_t characterSize,
		sf::Color textColor, sf::Color buttonColor);
	~Button();

	//Accessors
	const bool isPressed() const;

	//Functions
	void update(const sf::Vector2i& mousePos);
	void render(sf::RenderTarget* target);

private:
	bool m_pressed : 1;
	uint8_t m_buttonState : 1; 

    sf::RectangleShape m_shape;
	sf::Font* m_font;
	sf::Text m_text;

	sf::Color m_color;
};

#endif
