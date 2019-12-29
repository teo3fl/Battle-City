#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
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

	void UpdateInput(const float& dt) override;
	void UpdateMousePosition();
	void UpdateButtons();
	void Update(const float& dt) override;


	void RenderButtons(sf::RenderTarget* target = nullptr);
	void Render(sf::RenderTarget* target = nullptr) override;

private:

	sf::Texture m_backgroundTexture;
	sf::RectangleShape m_background;
	sf::Font m_font;
	std::stack<State*>* m_states;
	std::map<std::string, Button*> m_buttons;

	sf::Vector2i m_mousePosScreen;
	sf::Vector2i m_mousePosWindow;
};
#endif
