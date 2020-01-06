#pragma once

#include "State.h"
#include "TileMap.h"
#include "Player.h"
#include "Spawner.h"

enum class GameStatus
{
	NextStage = 0,
	CurrentStage,
	ScoreScreen,
	GameOver	
};

class SinglePlayerState :
   public State
{
public:
	SinglePlayerState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~SinglePlayerState();

	void Update(const float& dt) override;
	void Render(sf::RenderTarget* target = nullptr) override;
	
protected:
	void InitializeVariables();
	void InitializeKeybinds() override;
	void InitializeTextures();
	void InitializePlayer1();
	void InitializeFonts();
	void InitializeBackground();
	void InitializeMap();
	void InitializeSpawner();
	void InitializeEnemyLives();
	void InitializeScoreMap();

	void InitializeCurrentStage();
	void LoadMap(uint8_t stage);
	void LoadSpawner(uint8_t stage);
	virtual void ResetPlayerPosition();
	void CheckForGameOver(); 
	void CheckForNextStage();
	bool CheckForCollision(Tank* tank, Bullet* bullet, const float& dt);
		
	void UpdateInput(const float& dt) override;
	void UpdatePlayer1Movement(const float& dt);
	void UpdatePlayer1Fire(const float& dt);
	void UpdateEnemies(const float& dt);
	void UpdateSpawner(const float& dt);
	void UpdateMap(const float& dt);
	void UpdateStageBackground();
	void UpdateTankBulletCollision(Player* player, const float& dt);
	void UpdateEnemyLives();

	void RenderBackground(sf::RenderTarget* target);
	void RenderBullet(sf::RenderTarget* target, Tank* tank);
	virtual void RenderPlayers(sf::RenderTarget* target = nullptr);
	void RenderEnemies(sf::RenderTarget* target = nullptr);
	void RenderNextStateScreen(sf::RenderTarget* target = nullptr);
	void RenderCurrentStage(sf::RenderTarget* target = nullptr);
	void RenderScoreScreen(sf::RenderTarget* target = nullptr);
	void RenderGameOverScreen(sf::RenderTarget* target = nullptr);

protected:
	Player* m_player1;
	std::vector<Tank*> m_enemies;
	uint8_t m_numberOfEnemies;
	Spawner* m_spawner;
	std::vector<sf::RectangleShape> m_enemyLives;
	std::map<std::string, uint8_t> m_enemiesDestroied;

	sf::RectangleShape m_background;
	sf::RectangleShape m_transitionScreen;
	sf::RectangleShape m_scoreScreen;
	sf::RectangleShape m_gameOverScreen;

	GameStatus m_gameStatus;

	uint8_t m_currentStageNumber;
	uint8_t m_stages;

	sf::Font m_font;
	sf::Text m_stageScreenText;
	sf::Text m_stageNumberText;

	TileMap* m_map;
	uint16_t m_mapHeight;
	uint16_t m_mapWidth;
	std::vector<std::string> m_mapStages;
	std::vector<std::string> m_spawnStages;
};
