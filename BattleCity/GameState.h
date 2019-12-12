#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Player.h"

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
	void EndState() override;
	
	void UpdateInput(const float& dt) override;
	void Update(const float& dt) override;
	void Render(sf::RenderTarget* target = nullptr) override;
private:
	Player* m_player;

};
#endif
