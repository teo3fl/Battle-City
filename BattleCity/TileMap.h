#pragma once

#include "Brick.h"
#include "Ice.h"
#include "Steel.h"
#include "Trees.h"
#include "Water.h"

#include "Entity.h"

class TileMap
{
public:
	TileMap(uint16_t width, uint16_t height);
	~TileMap();

	void Clear();

	void LoadFromFile(const std::string& fileName);
	void AddTexture(const std::string& textureName, const sf::Texture& texture);

	void UpdateBorderCollision(Entity* entity, const float& dt);
	void UpdateTileCollision(Entity* entity, const float& dt);

	void Update (Entity* entity, const float& dt);
	void RenderTilesAbove(sf::RenderTarget* target = nullptr);
	void RenderTilesBelow(sf::RenderTarget* target = nullptr);

private:
	uint16_t m_width;
	uint16_t m_height;
	std::vector<std::vector<Tile*>> m_map;
	std::map<std::string, sf::Texture> m_textures;

	sf::Vector2f m_upperLeftCorner;
	sf::Vector2f m_lowerRightCorner;
};

