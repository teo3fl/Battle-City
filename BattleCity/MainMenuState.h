#pragma once

#include "SinglePlayerState.h"
#include "Button.h"
#include "KeybindState.h"

class MainMenuState :
	public State
{
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	//Functions
	void InitializeBackground();
	void InitializeButtons();
	void InitializeKeybinds() override;
	void InitializeFont();
	void InitializeText();

	void UpdateScore();
	void UpdateInput(const float& dt) override;
	void UpdateMousePosition();
	void UpdateButtons();
	void Update(const float& dt) override;


	void RenderButtons(sf::RenderTarget& target);
	void Render(sf::RenderTarget* target = nullptr) override;

private:

	sf::Texture m_backgroundTexture;
	sf::RectangleShape m_background;
	sf::Font m_font;
	std::stack<State*>* m_states;
	std::map<std::string, Button*> m_buttons;

	sf::Vector2i m_mousePosScreen;
	sf::Vector2i m_mousePosWindow;

	bool m_updateScore;
};
