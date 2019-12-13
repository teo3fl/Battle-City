#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Player.h"
#include "Button.h"

class GameState :
   public State
{

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~GameState();
	
	//Functions
	void InitializeKeybinds() override;
	void InitializeTextures();
	void InitializePlayer();
	void InitializeButtons();
	void InitializeFonts();
	void EndState() override;
	
	void UpdateInput(const float& dt) override;
	void Update(const float& dt) override;
	void Render(sf::RenderTarget* target = nullptr) override;
	void UpdateButtons();
	void RenderButtons(sf::RenderTarget* target = nullptr);

	
private:
	Player* m_player;
	std::map<std::string, Button*> m_buttons;

};
#endif
