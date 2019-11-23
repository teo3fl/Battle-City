#pragma once
#include <SFML/Graphics.hpp>

class Game
{ 
public:
	Game();
	Game(const Game& game);
	Game operator=(Game& game);
	~Game();
public:
	 sf::RenderWindow m_window;
};
