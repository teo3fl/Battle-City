﻿#pragma once

#include "GraphicsSettings.h"
#include "GameState.h"

#include <stack>

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
	void InitializeKeys();
	void InitializeStates();

	void UpdateDt();

	void Render();
	void Update();
	void UpdateSFMLEvents();

	void Run();

public:
	GraphicsSettings m_gfxSettings;
	sf::RenderWindow* m_window;
	sf::Event m_event;

	sf::Clock m_clock;
	float m_dt;

	std::stack<State*> m_states;

	std::map<char*, int> m_supportedKeys;
};
