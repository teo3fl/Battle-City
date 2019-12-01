#include "GameState.h"


GameState::GameState(sf::RenderWindow* window)
	: State(window)
{
}

GameState::~GameState()
{
}

void GameState::endState()
{
	std::cout << "Ending GameState!" << "\n";
}

void GameState::updateKeybinds(const float& dt)
{
	checkForQuit();
	
}


void GameState::update(const float& dt)
{
	updateKeybinds(dt);

	m_player.update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	m_player.render(*target);
}
