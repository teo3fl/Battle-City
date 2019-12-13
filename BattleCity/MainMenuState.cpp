#include "MainMenuState.h"


MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	InitializeKeybinds();
	m_background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	m_background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
	
}

void MainMenuState::InitializeKeybinds()
{
	std::ifstream in("../External/Resources/Config/gamestate_keybinds.ini");

	if (in.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (in >> key >> key2)
		{
			m_keybinds[key] = m_supportedKeys->at(key2);
		}
	}
	else
		throw "ERROR::GAME_STATE::KEYBINDS_NOT_FOUND";

	in.close();
}

void MainMenuState::EndState()
{
	std::cout << "Ending GameState!" << "\n";
}

void MainMenuState::UpdateInput(const float& dt)
{
	CheckForQuit();
}


void MainMenuState::Update(const float& dt)
{
	UpdateInput(dt);
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;

	target->draw(this->m_background);
}
