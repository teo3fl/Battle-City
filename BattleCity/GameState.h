#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState :
   public State
{
private:
	Entity m_player;
	
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~GameState();
	
	//Functions
	void InitializeKeybinds();
	void EndState() override;
	
	void UpdateInput(const float& dt) override;
	void Update(const float& dt) override;
	void Render(sf::RenderTarget* target = nullptr) override;
};
#endif
