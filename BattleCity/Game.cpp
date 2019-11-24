#include "Game.h"

Game::Game()
{
	
}


Game::~Game()
{
	
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

