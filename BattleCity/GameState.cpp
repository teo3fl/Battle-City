#include "stdafx.h"
#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	InitializeKeybinds();
	InitializeTextures();
	InitializeBackground();
	InitializePlayer();
	InitializeMap();
}

GameState::~GameState()
{
	delete m_player1;
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


	// tile textures

	if (!m_textures["BRICK"].loadFromFile("../External/Resources/Textures/brick.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BRICK_TEXTURE";
	}

	if (!m_textures["STEEL"].loadFromFile("../External/Resources/Textures/steel.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_STEEL_TEXTURE";
	}

	if (!m_textures["ICE"].loadFromFile("../External/Resources/Textures/ice.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_ICE_TEXTURE";
	}

	if (!m_textures["WATER"].loadFromFile("../External/Resources/Textures/water.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_WATER_TEXTURE";
	}

	if (!m_textures["TREES"].loadFromFile("../External/Resources/Textures/grass.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TREES_TEXTURE";
	}

	if (!m_textures["BACKGROUND"].loadFromFile("../External/Resources/Textures/gameBackground.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TREES_GAME_BACKGROUND";
	}
}

void GameState::InitializePlayer()
{
	m_player1 = new Player("Player1",340, 855);
	m_player1->AddTexture(m_textures["PLAYER1_RIGHT"], "RIGHT");
	m_player1->AddTexture(m_textures["PLAYER1_LEFT"], "LEFT");
	m_player1->AddTexture(m_textures["PLAYER1_UP"], "UP");
	m_player1->AddTexture(m_textures["PLAYER1_DOWN"], "DOWN");

	m_player1->SetTexture("UP");
}

void GameState::InitializeBackground()
{
	m_background.setSize(sf::Vector2f(1100.f, 1000.f));
	m_background.setTexture(&m_textures["BACKGROUND"]);
}

void GameState::InitializeMap()
{
	m_mapHeight = 26;
	m_mapWidth = 26;
	m_map = new TileMap(m_mapHeight, m_mapWidth);
	m_map->AddTexture("BRICK", m_textures["BRICK"]);
	m_map->AddTexture("STEEL", m_textures["STEEL"]);
	m_map->AddTexture("ICE", m_textures["ICE"]);
	m_map->AddTexture("WATER", m_textures["WATER"]);
	m_map->AddTexture("TREES", m_textures["TREES"]);

	m_map->LoadFromFile("../External/Resources/Config/map_stage3.ini");
}

void GameState::UpdateInput(const float& dt)
{
	CheckForQuit();
	UpdatePlayerMovement(dt);
}

void GameState::UpdatePlayerMovement(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->m_keybinds.at("MOVE_LEFT"))))
	{
		m_player1->Move(dt, -1.f, 0.f);
		m_player1->SetTexture("LEFT");
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->m_keybinds.at("MOVE_RIGHT"))))
	{
		m_player1->Move(dt, 1.f, 0.f);
		m_player1->SetTexture("RIGHT");
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->m_keybinds.at("MOVE_UP"))))
	{
		m_player1->Move(dt, 0.f, -1.f);
		m_player1->SetTexture("UP");
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->m_keybinds.at("MOVE_DOWN"))))
	{
		m_player1->Move(dt, 0.f, 1.f);
		m_player1->SetTexture("DOWN");
		return;
	}
}

void GameState::UpdateMap(const float& dt)
{
	m_map->Update(m_player1,dt);
}


void GameState::Update(const float& dt)
{
	UpdateKeytime(dt);
	UpdateInput(dt);

	m_player1->Update(dt);
	UpdateMap(dt);
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;

	target->draw(m_background);
	m_map->RenderTilesBelow(target);
	m_player1->Render(target);
	m_map->RenderTilesAbove(target);
}
