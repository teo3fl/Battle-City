#include "MainMenuState.h"


MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	InitializeKeybinds();
	InitializeBackground();
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

void MainMenuState::InitializeBackground()
{
	m_background.setSize(sf::Vector2f(1100.f, 1000.f));

	if (!m_backgroundTexture.loadFromFile("../External/Resources/Textures/cover.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	m_background.setTexture(&m_backgroundTexture);
}

void MainMenuState::InitializeButtons()
{
	this->m_buttons["GAME_STATE"] = new Button(100, 100, 150, 50,
		&this->m_font, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->m_buttons["EXIT_STATE"] = new Button(100, 300, 150, 50,
		&this->m_font, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

void MainMenuState::UpdateInput(const float& dt)
{
	CheckForQuit();
	
}

void MainMenuState::UpdateButtons(const sf::Vector2f& mousePos)
{
	for (auto& it : m_buttons)
	{
		it.second->update(mousePos);
		
	}
}


void MainMenuState::Update(const float& dt)
{
	UpdateInput(dt);
	UpdateButtons(mousePos);
	
}

void MainMenuState::RenderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->m_buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;

	target->draw(this->m_background);

	RenderButtons(target);
}
