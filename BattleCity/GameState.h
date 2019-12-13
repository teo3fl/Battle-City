#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
<<<<<<< Updated upstream
#include "Player.h"
=======
#include "Button.h"
>>>>>>> Stashed changes

class GameState :
   public State
{

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~GameState();
	
	//Functions
<<<<<<< Updated upstream
	void InitializeKeybinds() override;
	void InitializeTextures();
	void InitializePlayer();
=======
	void InitializeKeybinds();
	void InitializeButtons();
	void InitializeFonts();
>>>>>>> Stashed changes
	void EndState() override;
	
	void UpdateInput(const float& dt) override;
	void Update(const float& dt) override;
	void Render(sf::RenderTarget* target = nullptr) override;
	void UpdateButtons();
	void RenderButtons(sf::RenderTarget* target = nullptr);

	
private:
<<<<<<< Updated upstream
	Player* m_player;
=======
	Entity m_player;
	std::map<std::string, Button*> buttons;
>>>>>>> Stashed changes

};
#endif
