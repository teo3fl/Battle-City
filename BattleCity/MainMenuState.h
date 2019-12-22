#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"

class MainMenuState :
	public State
{
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~MainMenuState();

	//Functions
	void EndState() override;

	void InitializeBackground();
	void InitializeButtons();

	void UpdateInput(const float& dt) override;
	void UpdateButtons(const sf::Vector2f& mousePos);
	void Update(const float& dt) override;


	void RenderButtons(sf::RenderTarget* target = nullptr);
	void Render(sf::RenderTarget* target = nullptr) override;

private:

	sf::Texture m_backgroundTexture;
	sf::RectangleShape m_background;
	sf::Font m_font;

	void InitializeKeybinds() override;
};
#endif
