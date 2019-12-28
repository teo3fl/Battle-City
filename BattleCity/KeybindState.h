#pragma once
#include "State.h"
class KeybindState :
	public State
{
public:
	KeybindState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, 
		sf::Font* font, sf::Color color, uint8_t size);
	void InitializeKeybinds() override;
	void InitializeBackground();
	void InitializeText(sf::Color color, uint8_t size);

	void UpdateInput(const float& dt) override; 
	void Update(const float& dt) override;
	void Render(sf::RenderTarget* target = nullptr) override;
private:
	sf::RectangleShape m_background;
	sf::Text m_actions;
	sf::Text m_keybinds;
	sf::Font* m_font;
};

