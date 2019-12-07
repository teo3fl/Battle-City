#include "Game.h"

Game::Game()
{
	InitializeVariables();
	InitializeGraphics();
	InitializeWindow();
	InitializeKeys();
	InitializeStates();
}

Game::~Game()
{
	delete m_window;
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

void Game::InitializeKeys()
{
	m_supportedKeys.emplace("Escape", sf::Keyboard::Key::Escape);
	m_supportedKeys.emplace("D", sf::Keyboard::Key::D);
	m_supportedKeys.emplace("W", sf::Keyboard::Key::W);
	m_supportedKeys.emplace("S", sf::Keyboard::Key::S);
}

void Game::InitializeStates()
{
	m_states.push(new GameState(this->window, this->m_supportedKeys));
}

void Game::UpdateDt()
{
	// Updates the dt variable with the time it takes to update and render one frame.
	m_dt = m_clock.restart().asSeconds();
}

void Game::Render()
{
	m_window->clear();

	if (!m_states.empty())
		m_states.top()->render();

	m_window->display();
}

void Game::Update()
{
	UpdateSFMLEvents();

	if (!m_states.empty())
	{
		if (m_window->hasFocus())
		{
			m_states.top()->update(m_dt);

			if (m_states.top()->getQuit())
			{
				m_states.top()->endState();
				delete m_states.top();
				m_states.pop();
			}
		}
	}
	else
	{
		// end application

		m_window->close();
	}
}

void Game::UpdateSFMLEvents()
{
	while (m_window->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			m_window->close();
	}
}

void Game::Run()
{
	while (m_window->isOpen())
	{
		UpdateDt();
		Update();
		Render();
	}
}

