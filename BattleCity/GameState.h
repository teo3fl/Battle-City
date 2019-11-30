#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState :
   public State
{
private:
	
public:
	GameState(sf::RenderWindow* window);
	virtual ~GameState();
	
	//Functions
	void endState() override;
	
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};
#endif
