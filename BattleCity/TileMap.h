#pragma once

#include "Brick.h"
#include "Ice.h"
#include "Steel.h"
#include "Trees.h"
#include "Water.h"

class TileMap
{
public:
	TileMap(uint16_t width, uint16_t height);
	~TileMap();

	void InitializeBorders();
	void LoadFromFile(const std::string& fileName);
	void AddTexture(const std::string& textureName, const sf::Texture& texture);

	void Render(sf::RenderTarget* target = nullptr);

private:
	uint16_t m_width;
	uint16_t m_height;
	uint16_t m_border;
	std::vector<std::vector<Tile*>> m_map;
	std::map<std::string, sf::Texture> m_textures;

	sf::Sprite m_upperBorder;
	sf::Sprite m_lowerBorder;
	sf::Sprite m_leftBorder;
	sf::Sprite m_rightBorder;

	std::vector<Hitbox*> m_borders;
	uint8_t m_numberOfBorders;
};

