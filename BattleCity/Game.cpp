#include "Game.h"

Game::Game()
{
	InitializeVariables();
	InitializeGraphics();
	InitializeWindow();
}


Game::~Game()
{
	
}

void Game::InitializeVariables()
{
	m_window = NULL;
	m_dt = 0;
}

void Game::InitializeGraphics()
{
	m_gfxSettings.LoadFromFile("../External/Resources/Config/graphics.ini");
}

void Game::InitializeWindow()
{
	if (m_gfxSettings.m_fullscreen)
		m_window = new sf::RenderWindow(
			m_gfxSettings.m_resolution,
			m_gfxSettings.m_title,
			sf::Style::Fullscreen,
			m_gfxSettings.m_contextSettings);
	else
		m_window = new sf::RenderWindow(
			m_gfxSettings.m_resolution,
			m_gfxSettings.m_title,
			sf::Style::Titlebar | sf::Style::Close,
			m_gfxSettings.m_contextSettings);
	m_window->setFramerateLimit(m_gfxSettings.m_frameRateLimit);
	m_window->setVerticalSyncEnabled(m_gfxSettings.m_verticalSync);
}

void Game::UpdateDt()
{
	// Updates the dt variable with the time it takes to update and render one frame.
	m_dt = m_clock.restart().asSeconds();
}

