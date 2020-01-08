#include "stdafx.h"
#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys), m_states(states)
{
	InitializeKeybinds();
	InitializeBackground();
	InitializeFont();
	InitializeButtons();
	InitializeText();

	m_updateScore = false;
}

MainMenuState::~MainMenuState()
{
	auto it = m_buttons.begin();
	for (it = m_buttons.begin(); it != m_buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::InitializeKeybinds()
{
	std::ifstream in("../External/Resources/Config/mainmenustate_keybinds.ini");

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
		throw "ERROR::SINGLE_PLAYER_STATE::KEYBINDS_NOT_FOUND";

	in.close();
}

void MainMenuState::InitializeFont()
{
	if (!m_font.loadFromFile("../External/Resources/Fonts/Arial.ttf"))
	{
		throw "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_FONT_FROM_FILE";
	}
}

void MainMenuState::InitializeText()
{
	SetText(m_highScoreText, m_font, sf::Color::White, 50, sf::Vector2f(420.f, 70.f), 1.f);

	LoadHighScore();
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
	m_buttons["SINGLE_PLAYER"] = new Button(475, 600, 150, 50,
		&m_font, "1 Player", 30,
		sf::Color::White, sf::Color::Black);

	m_buttons["MULTIPLAYER"] = new Button(475, 650, 150, 50,
		&m_font, "2 Players", 30,
		sf::Color::White, sf::Color::Black);

	m_buttons["KEYBINDS"] = new Button(475, 700, 150, 50,
		&m_font, "Keybinds", 30,
		sf::Color::White, sf::Color::Black);

	m_buttons["EXIT_STATE"] = new Button(475, 750, 150, 50,
		&m_font, "Quit", 30,
		sf::Color::White, sf::Color::Black);
}

void MainMenuState::UpdateScore()
{
	if (m_updateScore)
	{
		LoadHighScore();
		m_updateScore = false;
	}
}

void MainMenuState::UpdateInput(const float& dt)
{
	CheckForQuit();
}

void MainMenuState::UpdateMousePosition()
{
	m_mousePosScreen = sf::Mouse::getPosition();
	m_mousePosWindow = sf::Mouse::getPosition(*m_window);
}

void MainMenuState::UpdateButtons()
{
	for (auto& it : m_buttons)
	{
		it.second->update(m_mousePosWindow);
	}

	if (m_buttons["SINGLE_PLAYER"]->isPressed())
	{
		m_states->push(new SinglePlayerState(m_window, m_supportedKeys));
		m_updateScore = true;
	}

	if (m_buttons["MULTIPLAYER"]->isPressed())
	{
		//m_states->push(new MultyplayerState(m_window, m_supportedKeys));
		m_updateScore = true;
	}

	if (m_buttons["KEYBINDS"]->isPressed())
	{
		m_states->push(new KeybindState(m_window, m_supportedKeys,&m_font,sf::Color::White,30));
	}

	if (m_buttons["EXIT_STATE"]->isPressed())
	{
		m_quit = true;
	}
}


void MainMenuState::Update(const float& dt)
{
	UpdateScore();
	UpdateMousePosition();
	UpdateInput(dt);
	UpdateButtons();
}

void MainMenuState::RenderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->m_buttons)
	{
		it.second->render(&target);
	}
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;

	target->draw(m_background);
	target->draw(m_highScoreText);

	RenderButtons(*target);
}
