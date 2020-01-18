#include "stdafx.h"
#include "SinglePlayerState.h"

SinglePlayerState::SinglePlayerState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	logger.Log(Logger::Level::Info, "SINGLE_PLAYER_STATE: Entered SinglePlayerState.");
	InitializeKeybinds();
	InitializeTextures();
	InitializeBackground();
	InitializePlayer1();
	InitializeMap();
	InitializeFonts();
	InitializeVariables(); 
	InitializeTankSpawner(); 
	InitializePowerUpSpawner();
	InitializeEnemyLives();
	LoadHighScore();

	logger.Log(Logger::Level::Info, "SINGLE_PLAYER_STATE: Started game.");
}

SinglePlayerState::~SinglePlayerState()
{
	delete m_player1;
	for (Tank* tank : m_enemies)
		delete tank;

	for (PowerUp* powerUp : m_powerUps)
		delete powerUp;

	logger.Log(Logger::Level::Info, "SINGLE_PLAYER_STATE: Exited SinglePlayerState.");
}

void SinglePlayerState::InitializeVariables()
{
	m_gameStatus = GameStatus::NextStage;
	m_currentStageNumber = 1;
	m_numberOfEnemies = 20;
	m_numberOfPowerUps = 3;
	m_stages = 4;
	m_timerPowerUp = false;
	m_timerMaxValue = 10;
	m_timerValue = 0;
	m_enemies.reserve(m_numberOfEnemies);
	m_powerUps.reserve(m_numberOfPowerUps);

	InitializeText();

	UpdateNextStageBackground();
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

	if (!m_textures["PLAYER1_RIGHT_PROTECTED"].loadFromFile("../External/Resources/Textures/tank1R_PROTECTED.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_PLAYER1_TEXTURE_R_PROTECTED";
	}

	if (!m_textures["PLAYER1_LEFT_PROTECTED"].loadFromFile("../External/Resources/Textures/tank1L_PROTECTED.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_PLAYER1_TEXTURE_L_PROTECTED";
	}

	if (!m_textures["PLAYER1_UP_PROTECTED"].loadFromFile("../External/Resources/Textures/tank1U_PROTECTED.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_PLAYER1_TEXTURE_U_PROTECTED";
	}

	if (!m_textures["PLAYER1_DOWN_PROTECTED"].loadFromFile("../External/Resources/Textures/tank1D_PROTECTED.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_PLAYER1_TEXTURE_D_PROTECTED";
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

	// game background

	if (!m_textures["BACKGROUND"].loadFromFile("../External/Resources/Textures/gameBackground.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_GAME_BACKGROUND";
	}

	// power-ups textures

	if (!m_textures["GRENADE"].loadFromFile("../External/Resources/Textures/bomb.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_GRENADE_TEXTURE";
	}

	if (!m_textures["HELMET"].loadFromFile("../External/Resources/Textures/helmet.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_HELMET_TEXTURE";
	}

	if (!m_textures["SHOVEL"].loadFromFile("../External/Resources/Textures/shovel.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_SHOVEL_TEXTURE";
	}

	if (!m_textures["STAR"].loadFromFile("../External/Resources/Textures/star.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_STAR_TEXTURE";
	}

	if (!m_textures["TANK"].loadFromFile("../External/Resources/Textures/tank.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_TANK_TEXTURE";
	}

	if (!m_textures["TIMER"].loadFromFile("../External/Resources/Textures/clock.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_TIMER_TEXTURE";
	}

	// game over screen texture

	if (!m_textures["GAME_OVER"].loadFromFile("../External/Resources/Textures/gameover.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_GAME_OVER_TEXTURE";
	}

	// score screen texture

	if (!m_textures["SCORE"].loadFromFile("../External/Resources/Textures/score.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_SCORE_TEXTURE";
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

	// enemy life texture

	if (!m_textures["ENEMY_LIFE"].loadFromFile("../External/Resources/Textures/enemyLife.png"))
	{
		throw "ERROR::SINGLE_PLAYER_STATE::COULD_NOT_LOAD_ENEMY_LIFE_TEXTURE_D";
	}
}

void SinglePlayerState::InitializePlayer1()
{
	m_player1 = new Player("Player1",340, 855);

	m_player1->AddTexture(m_textures["PLAYER1_RIGHT"], "RIGHT");
	m_player1->AddTexture(m_textures["PLAYER1_LEFT"], "LEFT");
	m_player1->AddTexture(m_textures["PLAYER1_UP"], "UP");
	m_player1->AddTexture(m_textures["PLAYER1_DOWN"], "DOWN");

	m_player1->AddTexture(m_textures["PLAYER1_RIGHT_PROTECTED"], "RIGHT_PROTECTED");
	m_player1->AddTexture(m_textures["PLAYER1_LEFT_PROTECTED"], "LEFT_PROTECTED");
	m_player1->AddTexture(m_textures["PLAYER1_UP_PROTECTED"], "UP_PROTECTED");
	m_player1->AddTexture(m_textures["PLAYER1_DOWN_PROTECTED"], "DOWN_PROTECTED");

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

	m_scoreScreen.setSize(sf::Vector2f(1100.f, 1000.f));
	m_scoreScreen.setTexture(&m_textures["SCORE"]);

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

	m_aiMapStages.resize(4);
	m_aiMapStages[0] = "../External/Resources/Config/map_stage1_ai.ini";
	m_aiMapStages[1] = "../External/Resources/Config/map_stage2_ai.ini";
	m_aiMapStages[2] = "../External/Resources/Config/map_stage3_ai.ini";
	m_aiMapStages[3] = "../External/Resources/Config/map_stage4_ai.ini";
}

void SinglePlayerState::InitializeTankSpawner()
{
	m_spawner = new TankSpawner(m_numberOfEnemies, 1);
	m_spawner->m_aiMap = m_map->m_aiMap;

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

void SinglePlayerState::InitializePowerUpSpawner()
{
	m_powerUpSpawner = new PowerUpSpawner(3);

	m_powerUpSpawner->AddTexture(m_textures["GRENADE"], "GRENADE");
	m_powerUpSpawner->AddTexture(m_textures["SHOVEL"], "SHOVEL");
	m_powerUpSpawner->AddTexture(m_textures["HELMET"], "HELMET");
	m_powerUpSpawner->AddTexture(m_textures["STAR"], "STAR");
	m_powerUpSpawner->AddTexture(m_textures["TANK"], "TANK");
	m_powerUpSpawner->AddTexture(m_textures["TIMER"], "TIMER");
}

void SinglePlayerState::InitializeEnemyLives()
{
	uint16_t borderX = 970;
	uint16_t borderY = 100;

	uint8_t size = 30;

	m_enemyLives.resize(m_numberOfEnemies);

	for (uint8_t row = 0, x = 0; x < m_numberOfEnemies; ++x, ++row)
	{
		uint16_t coordX = borderX;
		uint16_t coordY = borderY + row * (size + 5);

		m_enemyLives[x] = sf::RectangleShape(
			sf::Vector2f(size, size)
		);
		m_enemyLives[x].setTexture(&m_textures["ENEMY_LIFE"]);
		m_enemyLives[x].setPosition(
			sf::Vector2f(coordX, coordY)
		);

		m_enemyLives[++x] = sf::RectangleShape(
			sf::Vector2f(size, size)
		);
		m_enemyLives[x].setTexture(&m_textures["ENEMY_LIFE"]);
		m_enemyLives[x].setPosition(
			sf::Vector2f(coordX + size + 5, coordY)
		);
	}
}

void SinglePlayerState::InitializeScoreMap()
{
	m_enemiesDestroied["ArmorTank"] = 0;
	m_enemiesDestroied["BasicTank"] = 0;
	m_enemiesDestroied["FastTank"] = 0;
	m_enemiesDestroied["PowerTank"] = 0;
}

void SinglePlayerState::InitializeText()
{
	SetText(m_player1Lives, m_font, sf::Color::White,50, sf::Vector2f(1020.f, 600.f),1.f);

	SetText(m_stageScreenText, m_font, sf::Color::Black, 200, 4.f);
	SetText(m_stageNumberText, m_font, sf::Color::White, 60, 1.f);

	SetText(m_scoreText, m_font, sf::Color::White, 70, sf::Vector2f(100.f, 300.f), 1.f);
	SetText(m_highScoreText, m_font, sf::Color::White, 65, sf::Vector2f(590.f, 26.f), 2.f);
	SetText(m_pointsPerTankType, m_font, sf::Color::White, 48, sf::Vector2f(210.f, 408.f), 1.f);
	SetText(m_numberOfTanksDestroied, m_font, sf::Color::White, 48, sf::Vector2f(520.f, 408.f), 1.f);
	SetText(m_totalTanksDestroied, m_font, sf::Color::White, 40, sf::Vector2f(520.f, 820.f), 1.f);
}

void SinglePlayerState::LoadMap(uint8_t stage)
{
	if (m_map)
	{
		m_map->Clear();
	}
	m_map->LoadFromFile(m_mapStages[stage - 1]);
	m_map->m_aiMap->LoadFromFile(m_aiMapStages[stage - 1]);
}

void SinglePlayerState::LoadTankSpawner(uint8_t stage)
{
	m_spawner->LoadFromFile(m_spawnStages[stage - 1]);

	m_enemies.push_back(m_spawner->SpawnNext());
}

void SinglePlayerState::LoadPowerUpSpawner()
{
	while (!m_powerUps.empty())
	{
		delete m_powerUps[0];
		m_powerUps.erase(m_powerUps.begin());
	}
	m_powerUpSpawner->GeneratePowerUps();
}

void SinglePlayerState::InitializeCurrentStage()
{
	LoadMap(m_currentStageNumber);
	LoadTankSpawner(m_currentStageNumber);
	LoadPowerUpSpawner();
	InitializeEnemyLives();
	InitializeScoreMap();

	m_player1Lives.setString(std::to_string(m_player1->GetLives()));
	m_stageNumberText.setString(std::to_string(m_currentStageNumber));
	m_stageNumberText.setPosition(sf::Vector2f(1000.f, 810.f));

	UpdateNextStageBackground();

	Bullet* bullet = m_player1->GetBullet();
	if (bullet)
		m_player1->DestroyBullet(bullet);
	bullet = m_player1->GetSecondaryBullet();
	if (bullet)
		m_player1->DestroyBullet(bullet);


	ResetPlayer1Position();
	m_player1->SetProtected(5);

	m_gameStatus = GameStatus::CurrentStage;

	logger.Log(Logger::Level::Info, "SINGLE_PLAYER_STATE: Initialized stage " + std::to_string(m_currentStageNumber) + ".");

	++m_currentStageNumber;
}

void SinglePlayerState::ResetPlayer1Position()
{
	m_player1->SetPosition(340, 855);
}

void SinglePlayerState::CheckForGameOver()
{
	if (!m_map->GetBaseStatus() || m_player1->GetLives() < 0)
	{
		m_gameStatus = GameStatus::GameOver;
		logger.Log(Logger::Level::Info, "SINGLE_PLAYER_STATE: Game over.");
	}
}

void SinglePlayerState::CheckForNextStage()
{
	if (m_spawner->IsEmpty() && m_enemies.empty())
	{
		m_gameStatus = GameStatus::ScoreScreen;
		UpdateScoreBackground();

		logger.Log(Logger::Level::Info, "SINGLE_PLAYER_STATE: Finished stage.");
	}
}

void SinglePlayerState::ActivatePowerUp(PowerUpType powerUp)
{

	logger.Log(Logger::Level::Info, "SINGLE_PLAYER_STATE: Picked up power-up.");
	switch (powerUp)
	{
	case PowerUpType::Grenade:
	{
		while (!m_enemies.empty())
		{
			delete m_enemies.front();
			m_enemies.erase(m_enemies.begin());
		}
		break;
	}
	case PowerUpType::Helmet:
	{
		m_player1->SetProtected(15);
		break;
	}
	case PowerUpType::Shovel:
	{
		m_map->ActivateShovelPowerUp(); 
		break;
	}
	case PowerUpType::Star:
	{
		m_player1->IncreaseOffensivePower();
		break;
	}
	case PowerUpType::Tank:
	{
		m_player1->GiveExtraLife();
		m_player1Lives.setString(std::to_string(m_player1->GetLives()));
		break;
	}
	case PowerUpType::Timer:
	{
		m_timerPowerUp = true;
		break;
	}
	default:
		throw "ERROR::SINGLE_PLAYER_STATE::INVALID_POWER_UP_TYPE";
	}
}

void SinglePlayerState::DoTankBulletCollision(Player* player, Bullet* bullet,const float& dt)
{
	for (uint8_t i = 0; i < m_enemies.size(); ++i)
	{
		Tank* tank = m_enemies[i];
		if (CheckForCollision(tank, bullet, dt))
		{
			uint8_t tankHealth = tank->GetHealth();
			uint8_t bulletHealth = bullet->GetHealth();
			if (tankHealth > bulletHealth)
			{
				tank->DecreaseHealth(bulletHealth);
				player->DestroyBullet(bullet);
			}
			else
			{
				bullet->DecreaseHealth(tankHealth);
				m_enemies.erase(m_enemies.begin() + i);
				uint16_t score = tank->GetPoints();
				m_player1->IncreaseScore(score);
				++m_enemiesDestroied[tank->GetType()];
				if (tank->DropPowerUp())
					m_powerUps.push_back(m_powerUpSpawner->SpawnNext());
				delete tank;
				logger.Log(Logger::Level::Info, "SINGLE_PLAYER_STATE: Player destroyed EnemyTank.");
				UpdateEnemyLives();
			}
			return;
		}
	}
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds.at("FIRE"))) && GetKeytime())
	{
		m_player1->Fire();
	}
 }

void SinglePlayerState::UpdatePlayer1Bullets(const float& dt)
{
	Bullet* bullet = m_player1->GetBullet();
	if (bullet)
		bullet->Update(dt);
	bullet = m_player1->GetSecondaryBullet();
	if (bullet)
		bullet->Update(dt);
}

void SinglePlayerState::UpdateEnemyBullets(const float& dt)
{
	for (Tank* tank : m_enemies)
	{
		Bullet* bullet = tank->GetBullet();
		if (bullet)
			bullet->Update(dt);
	}
}

void SinglePlayerState::UpdateEnemies(const float& dt)
{
	if (!m_enemies.empty())
		for (Tank* tank : m_enemies)
		{
			tank->Update(dt);
			Bullet* bullet = tank->GetBullet();
			if (bullet)
				bullet->Update(dt);
		}
}

void SinglePlayerState::UpdateTankSpawner(const float& dt)
{
	if (m_spawner->Update(dt) && !m_spawner->IsEmpty())
		m_enemies.push_back(m_spawner->SpawnNext());
}

void SinglePlayerState::UpdateMap(const float& dt)
{
	if (m_map->IsLoaded())
	{
		Bullet* bullet;

		// update map for player1
		m_map->UpdateTank(m_player1, dt);
		bullet = m_player1->GetBullet();
		if (bullet)
			m_map->UpdateBullet(m_player1, bullet, dt);
		bullet = m_player1->GetSecondaryBullet();
		if (bullet)
			m_map->UpdateBullet(m_player1, bullet, dt);

		// update map for enemy tanks
		for (Tank* tank : m_enemies)
		{
			m_map->UpdateTank(tank, dt);
			bullet = tank->GetBullet();
			if (bullet)
				m_map->UpdateBullet(tank, bullet, dt);
		}
	}
	m_map->UpdateShovelPowerUp(dt);
}

void SinglePlayerState::UpdateNextStageBackground()
{
	std::stringstream ss;
	ss << "Stage " << std::to_string(m_currentStageNumber);

	m_stageScreenText.setString(ss.str());

	m_stageScreenText.setPosition(
		m_transitionScreen.getGlobalBounds().width / 2.f - m_stageScreenText.getGlobalBounds().width / 2.f,
		m_transitionScreen.getGlobalBounds().height / 2.f - m_stageScreenText.getGlobalBounds().height / 2.f
	);
}

void SinglePlayerState::UpdateScoreBackground()
{
	// stage number
	m_stageNumberText.setPosition(sf::Vector2f(590.f, 115.f));

	// score
	uint32_t score = m_player1->GetScore();
	m_scoreText.setString(std::to_string(score));
	if (score > m_highScore)
	{
		std::ofstream out("../External/Resources/Config/high_score.ini");
		out << score;
		m_highScore = score;
		m_highScoreText.setString(std::to_string(score));
	}

	// points
	std::stringstream ss;

	ss<<
		std::to_string(100*m_enemiesDestroied["BasicTank"]) << std::endl << std::endl<<
		std::to_string(200 * m_enemiesDestroied["FastTank"]) << std::endl << std::endl<<
		std::to_string(300 * m_enemiesDestroied["PowerTank"]) << std::endl << std::endl<<
		std::to_string(400 * m_enemiesDestroied["ArmorTank"]) << std::endl << std::endl;

	m_pointsPerTankType.setString(ss.str());

	// number of tanks
	ss.str(std::string());

	ss <<
		std::to_string(m_enemiesDestroied["BasicTank"]) << std::endl << std::endl <<
		std::to_string(m_enemiesDestroied["FastTank"]) << std::endl << std::endl <<
		std::to_string(m_enemiesDestroied["PowerTank"]) << std::endl << std::endl <<
		std::to_string(m_enemiesDestroied["ArmorTank"]) << std::endl << std::endl;

	m_numberOfTanksDestroied.setString(ss.str());

	// total
	ss.str(std::string());

	uint8_t total = 
		m_enemiesDestroied["BasicTank"] + 
		m_enemiesDestroied["FastTank"] + 
		m_enemiesDestroied["PowerTank"] + 
		m_enemiesDestroied["ArmorTank"];

	ss << std::to_string(total);

	m_totalTanksDestroied.setString(ss.str());
}

void SinglePlayerState::UpdateTankBulletCollision(Player* player, const float& dt)
{
	if (player && !m_enemies.empty())
	{
		Bullet* bullet = player->GetBullet();
		if (bullet)
			DoTankBulletCollision(player, bullet, dt);
		bullet = player->GetSecondaryBullet();
		if (bullet)
			DoTankBulletCollision(player, bullet, dt);
	}
}

void SinglePlayerState::UpdatePlayerBulletCollision(Player* player, const float& dt)
{
	for (Tank* tank : m_enemies)
	{
		Bullet* bullet = tank->GetBullet();
		if (bullet && CheckForCollision(player,bullet,dt))
		{
			player->DecreaseHealth(bullet->GetHealth());
			logger.Log(Logger::Level::Info, "SINGLE_PLAYER_STATE: Player1 got shot by EnemyTank.");
			tank->DestroyBullet(bullet);
		}
	}
}

void SinglePlayerState::UpdatePowerUpCollision(Player* player, const float& dt)
{
	if (!m_powerUps.empty())
	{
		for (uint8_t i = 0; i < m_powerUps.size(); ++i)
			if (CheckForCollision( m_powerUps[i], player, dt))
			{
				m_player1->IncreaseScore(m_powerUps[i]->GetPoints());
				ActivatePowerUp(m_powerUps[i]->GetType());
				delete m_powerUps[i];
				m_powerUps.erase(m_powerUps.begin() + i);
				return;
			}
	}
}

void SinglePlayerState::UpdateEnemyLives()
{
	m_enemyLives.erase(m_enemyLives.begin() + m_enemyLives.size() - 1);
}

void SinglePlayerState::UpdatePowerUpsAppearance(const float& dt)
{
	if (!m_powerUps.empty())
		for (uint8_t i = 0; i < m_powerUps.size(); ++i)
			if (!m_powerUps[i]->Update(dt))
			{
				m_powerUps.erase(m_powerUps.begin() + i);
				return;
			}
}

void SinglePlayerState::UpdateTimerPowerUp(const float& dt)
{
	if (m_timerPowerUp)
	{
		m_timerValue += dt;
		if (m_timerValue >= m_timerMaxValue)
		{
			m_timerPowerUp = false;
			m_timerValue = 0;
		}
	}
}

void SinglePlayerState::RenderBackground(sf::RenderTarget* target)
{
	target->draw(m_background);
	target->draw(m_stageNumberText);
	target->draw(m_player1Lives);

	for (auto& rectangle : m_enemyLives)
		target->draw(rectangle);
}

void SinglePlayerState::RenderBullet(sf::RenderTarget* target, Tank* tank)
{
	if (tank)
	{
		Bullet* bullet = tank->GetBullet();
		if (bullet)
			bullet->Render(target);
	}
}

void SinglePlayerState::RenderPlayers(sf::RenderTarget* target)
{
	Bullet* bullet = m_player1->GetBullet();
	if (bullet)
		bullet->Render(target);
	bullet = m_player1->GetSecondaryBullet();
	if (bullet)
		bullet->Render(target);

	m_player1->Render(target);
}

void SinglePlayerState::RenderPowerUps(sf::RenderTarget* target)
{
	if (!m_powerUps.empty())
		for (PowerUp* powerUp : m_powerUps)
		{
			powerUp ->Render(target);
		}
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

	if (m_gameStatus == GameStatus::CurrentStage)
	{
		UpdatePowerUpsAppearance(dt);
		m_player1->Update(dt);

		UpdateTimerPowerUp(dt);
		if (!m_timerPowerUp)
			UpdateEnemies(dt);

		UpdatePlayer1Bullets(dt);

		UpdatePlayer1Fire(dt);
		UpdateMap(dt);

		if (m_map->IsLoaded())
			CheckForGameOver();
		UpdateTankBulletCollision(m_player1, dt);
		UpdatePlayerBulletCollision(m_player1, dt);
		if (m_player1->GetHealth() < 1)
			ResetPlayer1Position();

		UpdatePowerUpCollision(m_player1, dt);
		UpdateTankSpawner(dt);
		CheckForNextStage();
	}
}

void SinglePlayerState::RenderNextStageScreen(sf::RenderTarget* target)
{
	if (m_currentStageNumber <= m_stages)
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds.at("CONTINUE"))) || !GetKeytime())
		{
			target->draw(m_transitionScreen);
			target->draw(m_stageScreenText);
		}
		else
			InitializeCurrentStage();
	else
		m_quit = true;
}

void SinglePlayerState::RenderCurrentStage(sf::RenderTarget* target)
{
	RenderBackground(target);

	m_map->RenderTilesBelow(target);

	RenderPlayers(target);
	RenderEnemies(target);

	m_map->RenderTilesAbove(target);
	RenderPowerUps(target);
}

void SinglePlayerState::RenderScoreScreen(sf::RenderTarget* target)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds.at("CONTINUE"))) || !GetKeytime())
	{
		target->draw(m_scoreScreen);
		target->draw(m_stageNumberText);
		target->draw(m_scoreText);
		target->draw(m_highScoreText);
		target->draw(m_pointsPerTankType);
		target->draw(m_numberOfTanksDestroied);
		target->draw(m_totalTanksDestroied);
	}
	else
	{
		m_gameStatus = GameStatus::NextStage;
		UpdateNextStageBackground();
	}
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
		RenderNextStageScreen(m_window);
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
	case GameStatus::ScoreScreen:
	{
		RenderScoreScreen(m_window);
		break;
	}
	}
}