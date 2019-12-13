#include "GameState.h"
#include <fstream>

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	InitializeKeybinds();
	InitializeTextures();
	InitializePlayer();
	InitializeButtons();
}

GameState::~GameState()
{
	EndState();
	delete m_player;
	auto it = m_buttons.begin();
	for (auto it = m_buttons.begin(); it != m_buttons.end(); ++it)
	{
		delete it->second;
	}
}

void GameState::InitializeKeybinds()
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

void GameState::InitializeTextures()
{
	if (!m_textures["PLAYER"].loadFromFile("../External/Resources/Textures/tank1R.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
}

void GameState::InitializePlayer()
{
	m_player = new Player(500, 500, m_textures["PLAYER"]);
}

void GameState::InitializeButtons()
{
}


void GameState::EndState()
{
	std::cout << "Ending GameState!" << "\n";
}

void GameState::UpdateInput(const float& dt)
{
	CheckForQuit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->m_keybinds.at("MOVE_LEFT"))))
		m_player->move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->m_keybinds.at("MOVE_RIGHT"))))
		m_player->move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->m_keybinds.at("MOVE_UP"))))
		m_player->move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->m_keybinds.at("MOVE_DOWN"))))
		m_player->move(dt, 0.f, 1.f);

}


void GameState::Update(const float& dt)
{
	UpdateInput(dt);

	m_player->update(dt);
}

void GameState::UpdateButtons()
{
	for (auto& it : this->m_buttons)
	{
		//it.second->update(this->m_mousePosView);
	}


	/*if (this->m_button[GAMESTATE_H]->isPressed())
		m_states.push(new GameState(m_window, &this->m_supportedKeys));*/
}

void GameState::RenderButtons(sf::RenderTarget* target)
{
	for (auto& it : m_buttons)
	{
		it.second->render(target);
	}
}


void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;

	m_player->render(target);
}
