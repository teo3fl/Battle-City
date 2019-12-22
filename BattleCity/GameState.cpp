#include "GameState.h"
#include <fstream>

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	InitializeKeybinds();
	InitializeTextures();
	InitializePlayer();
}

GameState::~GameState()
{
	EndState();
	delete m_player1;
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
	// player1 textures

	if (!m_textures["PLAYER1_RIGHT"].loadFromFile("../External/Resources/Textures/tank1R.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER1_TEXTURE_R";
	}

	if (!m_textures["PLAYER1_LEFT"].loadFromFile("../External/Resources/Textures/tank1L.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER1_TEXTURE_L";
	}

	if (!m_textures["PLAYER1_UP"].loadFromFile("../External/Resources/Textures/tank1U.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER1_TEXTURE_U";
	}

	if (!m_textures["PLAYER1_DOWN"].loadFromFile("../External/Resources/Textures/tank1D.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER1_TEXTURE_D";
	}

	
	// player2 textures


	if (!m_textures["PLAYER2_RIGHT"].loadFromFile("../External/Resources/Textures/tank2R.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER2_TEXTURE_R";
	}

	if (!m_textures["PLAYER2_LEFT"].loadFromFile("../External/Resources/Textures/tank2L.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER2_TEXTURE_L";
	}

	if (!m_textures["PLAYER2_UP"].loadFromFile("../External/Resources/Textures/tank2U.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER2_TEXTURE_U";
	}

	if (!m_textures["PLAYER2_DOWN"].loadFromFile("../External/Resources/Textures/tank2D.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER2_TEXTURE_D";
	}
}

void GameState::InitializePlayer()
{
	m_player1 = new Player(500, 500);
	m_player1->AddTexture(m_textures["PLAYER1_RIGHT"], "RIGHT");
	m_player1->AddTexture(m_textures["PLAYER1_LEFT"], "LEFT");
	m_player1->AddTexture(m_textures["PLAYER1_UP"], "UP");
	m_player1->AddTexture(m_textures["PLAYER1_DOWN"], "DOWN");

	m_player1->SetTexture("UP");
}

void GameState::EndState()
{
	std::cout << "Ending GameState!" << "\n";
}

void GameState::UpdateInput(const float& dt)
{
	CheckForQuit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->m_keybinds.at("MOVE_LEFT"))))
	{
		m_player1->Move(dt, -1.f, 0.f);
		m_player1->SetTexture("LEFT");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->m_keybinds.at("MOVE_RIGHT"))))
	{
		m_player1->Move(dt, 1.f, 0.f);
		m_player1->SetTexture("RIGHT");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->m_keybinds.at("MOVE_UP"))))
	{
		m_player1->Move(dt, 0.f, -1.f);
		m_player1->SetTexture("UP");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->m_keybinds.at("MOVE_DOWN"))))
	{
		m_player1->Move(dt, 0.f, 1.f);
		m_player1->SetTexture("DOWN");
	}

}


void GameState::Update(const float& dt)
{
	UpdateInput(dt);

	m_player1->Update(dt);
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;

	m_player1->Render(target);
}
