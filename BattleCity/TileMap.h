#pragma once

#include "Brick.h"
#include "Ice.h"
#include "Steel.h"
#include "Trees.h"
#include "Water.h"

#include "Tile.h"
#include "Entity.h"

#include <vector>

class TileMap
{
public:
	TileMap(float width,float height);
	void LoadFromFile(const std::string& fileName);
	void AddTexture(const std::string& textureName, const sf::Texture& texture);

private:
	uint16_t m_width;
	uint16_t m_height;
	uint16_t m_border;
	std::vector<std::vector<std::vector<Tile*>>> m_map;
	std::map<std::string, sf::Texture> m_textures;
};

