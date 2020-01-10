#pragma once

#include "State.h"
#include "TileMap.h"
#include "Player.h"
#include "TankSpawner.h"
#include "PowerUpSpawner.h"

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
	void InitializeTankSpawner();
	void InitializePowerUpSpawner();
	void InitializeEnemyLives();
	void InitializeScoreMap();
	void InitializeText();

	void InitializeCurrentStage();
	void LoadMap(uint8_t stage);
	void LoadTankSpawner(uint8_t stage);
	void LoadPowerUpSpawner();
	virtual void ResetPlayerPosition();
	void CheckForGameOver(); 
	void CheckForNextStage();
	void ActivatePowerUp(PowerUpType powerUp);

	template <class T, class U>
	bool CheckForCollision(T* object1, U* object2, const float& dt)
	{
		sf::FloatRect obj2Bounds = object2->GetGlobalBounds();
		sf::FloatRect nextPositionBounds = object2->GetNextPositionBounds(dt);
		sf::FloatRect obj1Bounds = object1->GetGlobalBounds();

		if (obj1Bounds.intersects(nextPositionBounds))
		{
			//Bottom collision
			if (obj2Bounds.top < obj1Bounds.top
				&& obj2Bounds.top + obj2Bounds.height < obj1Bounds.top + obj1Bounds.height
				&& obj2Bounds.left < obj1Bounds.left + obj1Bounds.width
				&& obj2Bounds.left + obj2Bounds.width > obj1Bounds.left
				)
				return true;

			//Top collision
			else if (obj2Bounds.top > obj1Bounds.top
				&& obj2Bounds.top + obj2Bounds.height > obj1Bounds.top + obj1Bounds.height
				&& obj2Bounds.left < obj1Bounds.left + obj1Bounds.width
				&& obj2Bounds.left + obj2Bounds.width > obj1Bounds.left
				)
				return true;

			//Right collision
			if (obj2Bounds.left < obj1Bounds.left
				&& obj2Bounds.left + obj2Bounds.width < obj1Bounds.left + obj1Bounds.width
				&& obj2Bounds.top < obj1Bounds.top + obj1Bounds.height
				&& obj2Bounds.top + obj2Bounds.height > obj1Bounds.top
				)
				return true;

			//Left collision
			else if (obj2Bounds.left > obj1Bounds.left
				&& obj2Bounds.left + obj2Bounds.width > obj1Bounds.left + obj1Bounds.width
				&& obj2Bounds.top < obj1Bounds.top + obj1Bounds.height
				&& obj2Bounds.top + obj2Bounds.height > obj1Bounds.top
				)
				return true;
		}
		return false;
	}
		
	void UpdateInput(const float& dt) override;
	void UpdatePlayer1Movement(const float& dt);
	void UpdatePlayer1Fire(const float& dt);
	void UpdateEnemies(const float& dt);
	void UpdateTankSpawner(const float& dt);
	void UpdateMap(const float& dt);
	void UpdateNextStageBackground();
	void UpdateScoreBackground();
	void UpdatePowerUpCollision(Player* player, const float& dt);
	void UpdateTankBulletCollision(Player* player, const float& dt);
	void UpdateEnemyLives();
	void UpdatePowerUps(const float& dt);

	void RenderBackground(sf::RenderTarget* target);
	void RenderBullet(sf::RenderTarget* target, Tank* tank);
	virtual void RenderPlayers(sf::RenderTarget* target = nullptr);
	void RenderPowerUps(sf::RenderTarget* target = nullptr);
	void RenderEnemies(sf::RenderTarget* target = nullptr);
	void RenderNextStageScreen(sf::RenderTarget* target = nullptr);
	void RenderCurrentStage(sf::RenderTarget* target = nullptr);
	void RenderScoreScreen(sf::RenderTarget* target = nullptr);
	void RenderGameOverScreen(sf::RenderTarget* target = nullptr);

protected:
	Player* m_player1;
	std::vector<Tank*> m_enemies;
	uint8_t m_numberOfEnemies;
	TankSpawner* m_spawner;
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
	sf::Text m_scoreText;
	sf::Text m_pointsPerTankType;
	sf::Text m_numberOfTanksDestroied;
	sf::Text m_totalTanksDestroied;

	TileMap* m_map;
	uint16_t m_mapHeight;
	uint16_t m_mapWidth;
	std::vector<std::string> m_mapStages;
	std::vector<std::string> m_spawnStages;

	// power-ups

	PowerUpSpawner* m_powerUpSpawner;
	std::vector<PowerUp*> m_powerUps;
	uint8_t m_numberOfPowerUps;

	bool m_timerPowerUp; // temporarily freezes time, stopping all enemy tanks' movement
};
