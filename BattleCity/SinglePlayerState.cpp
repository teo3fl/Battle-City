#include "stdafx.h"
#include "SinglePlayerState.h"

SinglePlayerState::SinglePlayerState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	InitializeKeybinds();
	InitializeTextures();
	InitializeBackground();
	InitializePlayer1();
	InitializeMap();
	InitializeFonts();
	InitializeVariables(); 
	InitializeSpawner();
}

SinglePlayerState::~SinglePlayerState()
{
	delete m_player1;
	for (Tank* tank : m_enemies)
		delete tank;
}

void SinglePlayerState::InitializeVariables()
{
	m_gameStatus = GameStatus::NextStage;
	m_stageNumber = 1;

	m_enemies.reserve(20);

	m_text.setFillColor(sf::Color::Black);
	m_text.setFont(m_font);
	m_text.setCharacterSize(200);
	m_text.setOutlineThickness(4.f);

	UpdateStageBackground();
}

void SinglePlayerState::InitializeKeybinds()
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
		throw "ERROR::SINGLE_PLAYER_STATE::KEYBINDS_NOT_FOUND";

	in.close();
}

void SinglePlayerState::InitializeTextures()
{
	// player1 textures

	if (!m_textures["PLAYER1_RIGHT"].loadFromFile("../External/Resources/Textures/tank1R.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_PLAYER1_TEXTURE_R";
	}

	if (!m_textures["PLAYER1_LEFT"].loadFromFile("../External/Resources/Textures/tank1L.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_PLAYER1_TEXTURE_L";
	}

	if (!m_textures["PLAYER1_UP"].loadFromFile("../External/Resources/Textures/tank1U.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_PLAYER1_TEXTURE_U";
	}

	if (!m_textures["PLAYER1_DOWN"].loadFromFile("../External/Resources/Textures/tank1D.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_PLAYER1_TEXTURE_D";
	}

	
	// player2 textures

	if (!m_textures["PLAYER2_RIGHT"].loadFromFile("../External/Resources/Textures/tank2R.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_PLAYER2_TEXTURE_R";
	}

	if (!m_textures["PLAYER2_LEFT"].loadFromFile("../External/Resources/Textures/tank2L.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_PLAYER2_TEXTURE_L";
	}

	if (!m_textures["PLAYER2_UP"].loadFromFile("../External/Resources/Textures/tank2U.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_PLAYER2_TEXTURE_U";
	}

	if (!m_textures["PLAYER2_DOWN"].loadFromFile("../External/Resources/Textures/tank2D.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_PLAYER2_TEXTURE_D";
	}


	// tile textures

	if (!m_textures["BRICK"].loadFromFile("../External/Resources/Textures/brick.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_BRICK_TEXTURE";
	}

	if (!m_textures["STEEL"].loadFromFile("../External/Resources/Textures/steel.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_STEEL_TEXTURE";
	}

	if (!m_textures["ICE"].loadFromFile("../External/Resources/Textures/ice.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_ICE_TEXTURE";
	}

	if (!m_textures["WATER"].loadFromFile("../External/Resources/Textures/water.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_WATER_TEXTURE";
	}

	if (!m_textures["TREES"].loadFromFile("../External/Resources/Textures/grass.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_TREES_TEXTURE";
	}

	if (!m_textures["BACKGROUND"].loadFromFile("../External/Resources/Textures/gameBackground.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_TREES_GAME_BACKGROUND";
	}

	// game over screen texture

	if (!m_textures["GAME_OVER"].loadFromFile("../External/Resources/Textures/gameover.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_GAME_OVER_TEXTURE";
	}

	// base texture

	if (!m_textures["BASE"].loadFromFile("../External/Resources/Textures/eagle.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_EAGLE_TEXTURE";
	}

	// bullet textures

	if (!m_textures["BULLET_UP"].loadFromFile("../External/Resources/Textures/bullet_U.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_BULLET_U_TEXTURE";
	}

	if (!m_textures["BULLET_DOWN"].loadFromFile("../External/Resources/Textures/bullet_D.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_BULLET_D_TEXTURE";
	}

	if (!m_textures["BULLET_LEFT"].loadFromFile("../External/Resources/Textures/bullet_L.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_BULLET_L_TEXTURE";
	}

	if (!m_textures["BULLET_RIGHT"].loadFromFile("../External/Resources/Textures/bullet_R.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_BULLET_R_TEXTURE";
	}


	// enemy tanks textures

	if (!m_textures["ARMOR_TANK_RIGHT"].loadFromFile("../External/Resources/Textures/enemyTank4R.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_ARMOR_TANK_TEXTURE_R";
	}

	if (!m_textures["ARMOR_TANK_LEFT"].loadFromFile("../External/Resources/Textures/enemyTank4L.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_ARMOR_TANK_TEXTURE_L";
	}

	if (!m_textures["ARMOR_TANK_UP"].loadFromFile("../External/Resources/Textures/enemyTank4U.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_ARMOR_TANK_TEXTURE_U";
	}

	if (!m_textures["ARMOR_TANK_DOWN"].loadFromFile("../External/Resources/Textures/enemyTank4D.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_ARMOR_TANK_TEXTURE_D";
	}


	if (!m_textures["BASIC_TANK_RIGHT"].loadFromFile("../External/Resources/Textures/enemyTank1R.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_BASIC_TANK_TEXTURE_R";
	}

	if (!m_textures["BASIC_TANK_LEFT"].loadFromFile("../External/Resources/Textures/enemyTank1L.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_BASIC_TANK_TEXTURE_L";
	}

	if (!m_textures["BASIC_TANK_UP"].loadFromFile("../External/Resources/Textures/enemyTank1U.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_BASIC_TANK_TEXTURE_U";
	}

	if (!m_textures["BASIC_TANK_DOWN"].loadFromFile("../External/Resources/Textures/enemyTank1D.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_BASIC_TANK_TEXTURE_D";
	}


	if (!m_textures["FAST_TANK_RIGHT"].loadFromFile("../External/Resources/Textures/enemyTank2R.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_FAST_TANK_TEXTURE_R";
	}

	if (!m_textures["FAST_TANK_LEFT"].loadFromFile("../External/Resources/Textures/enemyTank2L.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_FAST_TANK_TEXTURE_L";
	}

	if (!m_textures["FAST_TANK_UP"].loadFromFile("../External/Resources/Textures/enemyTank2U.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_FAST_TANK_TEXTURE_U";
	}

	if (!m_textures["FAST_TANK_DOWN"].loadFromFile("../External/Resources/Textures/enemyTank2D.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_FAST_TANK_TEXTURE_D";
	}


	if (!m_textures["POWER_TANK_RIGHT"].loadFromFile("../External/Resources/Textures/enemyTank3R.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_POWER_TANK_TEXTURE_R";
	}

	if (!m_textures["POWER_TANK_LEFT"].loadFromFile("../External/Resources/Textures/enemyTank3L.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_POWER_TANK_TEXTURE_L";
	}

	if (!m_textures["POWER_TANK_UP"].loadFromFile("../External/Resources/Textures/enemyTank3U.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_POWER_TANK_TEXTURE_U";
	}

	if (!m_textures["POWER_TANK_DOWN"].loadFromFile("../External/Resources/Textures/enemyTank3D.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_POWER_TANK_TEXTURE_D";
	}
}

void SinglePlayerState::InitializePlayer1()
{
	m_player1 = new Player("Player1",340, 855);

	m_player1->AddTexture(m_textures["PLAYER1_RIGHT"], "RIGHT");
	m_player1->AddTexture(m_textures["PLAYER1_LEFT"], "LEFT");
	m_player1->AddTexture(m_textures["PLAYER1_UP"], "UP");
	m_player1->AddTexture(m_textures["PLAYER1_DOWN"], "DOWN");

	m_player1->AddTexture(m_textures["BULLET_LEFT"], "BULLET_LEFT");
	m_player1->AddTexture(m_textures["BULLET_RIGHT"], "BULLET_RIGHT");
	m_player1->AddTexture(m_textures["BULLET_UP"], "BULLET_UP");
	m_player1->AddTexture(m_textures["BULLET_DOWN"], "BULLET_DOWN");

	m_player1->SetTexture("UP");
}

void SinglePlayerState::InitializeFonts()
{
	if (!m_font.loadFromFile("../External/Resources/Fonts/Arial.ttf"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_FONT_FROM_FILE";
	}
}

void SinglePlayerState::InitializeBackground()
{
	m_background.setSize(sf::Vector2f(1100.f, 1000.f));
	m_background.setTexture(&m_textures["BACKGROUND"]);

	m_transitionScreen.setSize(sf::Vector2f(1100.f, 1000.f));
	m_transitionScreen.setFillColor(sf::Color(225, 225, 225, 200));

	m_gameOverScreen.setSize(sf::Vector2f(1100.f, 1000.f));
	m_gameOverScreen.setTexture(&m_textures["GAME_OVER"]);
}

void SinglePlayerState::InitializeMap()
{
	m_mapHeight = 52;
	m_mapWidth = 52;
	m_map = new TileMap(m_mapHeight, m_mapWidth);
	m_map->AddTexture("BRICK", m_textures["BRICK"]);
	m_map->AddTexture("STEEL", m_textures["STEEL"]);
	m_map->AddTexture("ICE", m_textures["ICE"]);
	m_map->AddTexture("WATER", m_textures["WATER"]);
	m_map->AddTexture("TREES", m_textures["TREES"]);
	m_map->AddTexture("BASE", m_textures["BASE"]);

	m_mapStages.resize(4);
	m_mapStages[0] = "../External/Resources/Config/map_stage1.ini";
	m_mapStages[1] = "../External/Resources/Config/map_stage2.ini";
	m_mapStages[2] = "../External/Resources/Config/map_stage3.ini";
	m_mapStages[3] = "../External/Resources/Config/map_stage4.ini";
}

void SinglePlayerState::InitializeSpawner()
{
	m_spawner = new Spawner(20, 10);

	m_spawner->AddTexture(m_textures["BULLET_UP"], "BULLET_UP");
	m_spawner->AddTexture(m_textures["BULLET_DOWN"], "BULLET_DOWN");
	m_spawner->AddTexture(m_textures["BULLET_LEFT"], "BULLET_LEFT");
	m_spawner->AddTexture(m_textures["BULLET_RIGHT"], "BULLET_RIGHT");

	m_spawner->AddTexture(m_textures["ARMOR_TANK_UP"], "ARMOR_TANK_UP");
	m_spawner->AddTexture(m_textures["ARMOR_TANK_DOWN"], "ARMOR_TANK_DOWN");
	m_spawner->AddTexture(m_textures["ARMOR_TANK_LEFT"], "ARMOR_TANK_LEFT");
	m_spawner->AddTexture(m_textures["ARMOR_TANK_RIGHT"], "ARMOR_TANK_RIGHT");

	m_spawner->AddTexture(m_textures["BASIC_TANK_UP"], "BASIC_TANK_UP");
	m_spawner->AddTexture(m_textures["BASIC_TANK_DOWN"], "BASIC_TANK_DOWN");
	m_spawner->AddTexture(m_textures["BASIC_TANK_LEFT"], "BASIC_TANK_LEFT");
	m_spawner->AddTexture(m_textures["BASIC_TANK_RIGHT"], "BASIC_TANK_RIGHT");

	m_spawner->AddTexture(m_textures["FAST_TANK_UP"], "FAST_TANK_UP");
	m_spawner->AddTexture(m_textures["FAST_TANK_DOWN"], "FAST_TANK_DOWN");
	m_spawner->AddTexture(m_textures["FAST_TANK_LEFT"], "FAST_TANK_LEFT");
	m_spawner->AddTexture(m_textures["FAST_TANK_RIGHT"], "FAST_TANK_RIGHT");

	m_spawner->AddTexture(m_textures["POWER_TANK_UP"], "POWER_TANK_UP");
	m_spawner->AddTexture(m_textures["POWER_TANK_DOWN"], "POWER_TANK_DOWN");
	m_spawner->AddTexture(m_textures["POWER_TANK_LEFT"], "POWER_TANK_LEFT");
	m_spawner->AddTexture(m_textures["POWER_TANK_RIGHT"], "POWER_TANK_RIGHT");

	m_spawnStages.resize(4);
	m_spawnStages[0] = "../External/Resources/Config/spawner_stage1.ini";
	m_spawnStages[1] = "../External/Resources/Config/spawner_stage2.ini";
	m_spawnStages[2] = "../External/Resources/Config/spawner_stage3.ini";
	m_spawnStages[3] = "../External/Resources/Config/spawner_stage4.ini";
}

void SinglePlayerState::LoadMap(uint8_t stage)
{
	if (m_map)
	{
		m_map->Clear();
	}
	m_map->LoadFromFile(m_mapStages[stage-1]);
}

void SinglePlayerState::LoadSpawner(uint8_t stage)
{
	m_spawner->LoadFromFile(m_spawnStages[stage - 1]);

	m_enemies.push_back(m_spawner->SpawnNext());
}

void SinglePlayerState::InitializeCurrentStage()
{
	m_gameStatus = GameStatus::CurrentStage;
	LoadMap(m_stageNumber);
	LoadSpawner(m_stageNumber);
	++m_stageNumber;
	UpdateStageBackground();
	ResetPlayerPosition();
}

void SinglePlayerState::ResetPlayerPosition()
{
	m_player1->SetPosition(340, 855);
}

void SinglePlayerState::CheckForGameOver()
{
	if (!m_map->GetBaseStatus())
		m_gameStatus = GameStatus::GameOver;
}

void SinglePlayerState::UpdateInput(const float& dt)
{
	CheckForQuit();
	UpdatePlayer1Movement(dt);
}

void SinglePlayerState::UpdatePlayer1Movement(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds.at("MOVE_LEFT"))))
	{
		m_player1->Move(dt, -1.f, 0.f);
		m_player1->SetFacingDirection("LEFT");
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds.at("MOVE_RIGHT"))))
	{
		m_player1->Move(dt, 1.f, 0.f);
		m_player1->SetFacingDirection("RIGHT");
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds.at("MOVE_UP"))))
	{
		m_player1->Move(dt, 0.f, -1.f);
		m_player1->SetFacingDirection("UP");
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds.at("MOVE_DOWN"))))
	{
		m_player1->Move(dt, 0.f, 1.f);
		m_player1->SetFacingDirection("DOWN");
		return;
	}
}

void SinglePlayerState::UpdatePlayer1Fire(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds.at("FIRE"))))
	{
		m_player1->Fire();
	}
}

void SinglePlayerState::UpdateEnemies(const float& dt)
{
	if (!m_enemies.empty())
		for (Tank* tank : m_enemies)
			tank->Update(dt);
}

void SinglePlayerState::UpdateSpawner(const float& dt)
{
	if (m_spawner->Update(dt))
		m_enemies.push_back(m_spawner->SpawnNext());
}

void SinglePlayerState::UpdateMap(const float& dt)
{
	m_map->UpdateTank(m_player1,dt);
	Bullet* bullet = m_player1->GetBullet();
	if (bullet)
		m_map->UpdateBullet(m_player1, bullet,dt);
}

void SinglePlayerState::UpdateStageBackground()
{
	std::stringstream ss;
	ss << "Stage " << std::to_string(m_stageNumber);

	m_text.setString(ss.str());

	m_text.setPosition(
		m_transitionScreen.getGlobalBounds().width / 2.f - m_text.getGlobalBounds().width / 2.f,
		m_transitionScreen.getGlobalBounds().height / 2.f - m_text.getGlobalBounds().height / 2.f
	);
}

void SinglePlayerState::RenderBullet(sf::RenderTarget* target, Tank* tank)
{
	Bullet* bullet = tank->GetBullet();
	if (bullet)
		bullet->Render(target);
}

void SinglePlayerState::RenderPlayers(sf::RenderTarget* target)
{
	Bullet* bullet = m_player1->GetBullet();
	if (bullet)
		bullet->Render(target);

	m_player1->Render(target);
}

void SinglePlayerState::RenderEnemies(sf::RenderTarget* target)
{
	if (!m_enemies.empty())
		for (Tank* enemy : m_enemies)
		{
			RenderBullet(target, enemy);
			enemy->Render(target);
		}
}

void SinglePlayerState::Update(const float& dt)
{
	UpdateKeytime(dt);
	UpdateInput(dt);

	m_player1->Update(dt);
	UpdateEnemies(dt);
	Bullet* bullet = m_player1->GetBullet();
	if (bullet)
		bullet->Update(dt);

	UpdatePlayer1Fire(dt);
	UpdateMap(dt);
	//UpdateSpawner(dt);

	if (m_map->IsLoaded())
		CheckForGameOver();
}

void SinglePlayerState::RenderNextStateScreen(sf::RenderTarget* target)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds.at("CONTINUE"))))
	{
		target->draw(m_transitionScreen);
		target->draw(m_text);
	}
	else
		InitializeCurrentStage();
}

void SinglePlayerState::RenderCurrentStage(sf::RenderTarget* target)
{
	target->draw(m_background);

	m_map->RenderTilesBelow(target);

	RenderPlayers(target);
	RenderEnemies(target);

	m_map->RenderTilesAbove(target);
}

void SinglePlayerState::RenderGameOverScreen(sf::RenderTarget* target)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds.at("CLOSE"))))
		target->draw(m_gameOverScreen);
	else
		m_quit = true;
}

void SinglePlayerState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;

	switch (m_gameStatus)
	{
	case GameStatus::NextStage:
	{
		RenderNextStateScreen(m_window);
		break;
	}

	case GameStatus::GameOver:
	{
		RenderGameOverScreen(m_window);
		break;
	}

	case GameStatus::CurrentStage:
	{
		RenderCurrentStage(m_window);
		break;
	}
	}
}