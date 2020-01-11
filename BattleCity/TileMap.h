#pragma once

#include "Brick.h"
#include "Ice.h"
#include "Steel.h"
#include "Trees.h"
#include "Water.h"
#include "Base.h"

#include "Bullet.h"
#include "Tank.h"

class TileMap
{
public:
	TileMap(uint16_t width, uint16_t height);
	~TileMap();

	void Clear();

	void LoadFromFile(const std::string& fileName);
	void AddTexture(const std::string& textureName, const sf::Texture& texture);
	bool GetBaseStatus();
	bool IsLoaded();
	void ActivateShovelPowerUp();
	void FortifyBaseWalls();
	void RevertBaseWalls();

	void UpdateTankBorderCollision(Tank* tank, const float& dt);
	void UpdateTankTileCollision(Tank* tank, const float& dt);
	void UpdateTank (Tank* tank, const float& dt);
	void UpdateShovelPowerUp(const float& dt);

	bool UpdateBulletBorderCollision(Tank* tank, Bullet* bullet, const float& dt);
	void UpdateBulletTileCollision(Tank* tank, Bullet* bullet, const float& dt);
	void UpdateBullet(Tank* tank, Bullet* bullet, const float& dt);

	void RenderTilesAbove(sf::RenderTarget* target = nullptr);
	void RenderTilesBelow(sf::RenderTarget* target = nullptr);

private:
	uint16_t m_width;
	uint16_t m_height;
	std::vector<std::vector<Tile*>> m_map;
	std::map<std::string, sf::Texture> m_textures;

	sf::Vector2f m_upperLeftCorner;
	sf::Vector2f m_lowerRightCorner;

	sf::Vector2i m_baseCoordinates;
	bool m_loaded;

	// power-ups

	bool m_shovelPowerUp;
	float m_shovelTime;
	float m_shovelTimeMax;
};

