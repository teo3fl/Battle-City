#pragma once

#include "State.h"
#include "TileMap.h"
#include "Player.h"

class SinglePlayerState :
   public State
{

public:
	SinglePlayerState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~SinglePlayerState();
	
	//Functions
	void InitializeKeybinds() override;
	void InitializeTextures();
	void InitializePlayer();
	void InitializeFonts();
	void InitializeBackground();
	void InitializeMap();
		
	void UpdateInput(const float& dt) override;
	void UpdatePlayerMovement(const float& dt);
	void UpdateMap(const float& dt);
	void Update(const float& dt) override;
	void Render(sf::RenderTarget* target = nullptr) override;

	
private:
	Player* m_player1;
	sf::RectangleShape m_background;

	TileMap* m_map;
	uint16_t m_mapHeight;
	uint16_t m_mapWidth;
};
