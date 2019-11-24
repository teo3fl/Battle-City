#pragma once
#include "GraphicsSettings.h"

class Game
{ 
public:
	Game();
	Game(const Game& game);
	Game operator=(Game& game);
	~Game();

	void InitializeVariables();
	void InitializeGraphics();
	void InitializeWindow();

	void UpdateDt();

public:
	GraphicsSettings m_gfxSettings;
	sf::RenderWindow* m_window;

	sf::Clock m_clock;
	float m_dt;
};
