#pragma once

#include "State.h"
#include "TileMap.h"
#include "Player.h"

enum class GameStatus
{
	NextStage = 0,
	CurrentStage,
	GameOver	
};

class SinglePlayerState :
   public State
{
public:
	SinglePlayerState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~SinglePlayerState();
	
	//Functions
	void InitializeVariables();
	void InitializeKeybinds() override;
	void InitializeTextures();
	void InitializePlayer1();
	void InitializeFonts();
	void InitializeBackground();
	void InitializeMap();
	void InitializeBase();

	void LoadMap(uint8_t stage);
	void InitializeCurrentStage();
	void ResetPlayerPosition();
	void CheckForGameOver();
		
	void UpdateInput(const float& dt) override;
	void UpdatePlayer1Movement(const float& dt);
	void UpdatePlayer1Fire(const float& dt);
	void UpdateMap(const float& dt);
	void UpdateStageBackground();
	void Update(const float& dt) override;

	void RenderNextStateScreen(sf::RenderTarget* target = nullptr);
	void RenderCurrentStage(sf::RenderTarget* target = nullptr);
	void RenderGameOverScreen(sf::RenderTarget* target = nullptr);
	void Render(sf::RenderTarget* target = nullptr) override;

private:
	Player* m_player1;
	sf::RectangleShape m_background;
	sf::RectangleShape m_transitionScreen;
	sf::RectangleShape m_gameOverScreen;

	GameStatus m_gameStatus;

	uint8_t m_stageNumber;

	sf::Font m_font;
	sf::Text m_text;

	TileMap* m_map;
	uint16_t m_mapHeight;
	uint16_t m_mapWidth;
	std::vector<std::string> m_mapStages;
};
