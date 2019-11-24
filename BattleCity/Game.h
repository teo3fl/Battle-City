#pragma once
//#include <SFML/Graphics.hpp>
#include "GraphicsSettings.h"

class Game
{ 
public:
	Game();
	Game(const Game& game);
	Game operator=(Game& game);
	~Game();

	void InitializeGraphics();
	void InitializeWindow();

public:
	GraphicsSettings m_gfxSettings;
	 sf::RenderWindow m_window;
};
