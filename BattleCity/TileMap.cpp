#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(uint16_t width, uint16_t height) :
	m_width(width), m_height(height)
{
	m_border = 80;

	m_map.resize(m_height);
	for (int x = 0; x < m_height; x++)
		m_map[x].resize(m_width);

	InitializeBorders();
}

TileMap::~TileMap()
{
	for (int x = 0; x < m_height; x++)
		for (int y = 0; y < m_width; y++)
			if (m_map[x][y])
				delete m_map[x][y];
}

void TileMap::InitializeBorders()
{
	m_numberOfBorders = 4;
	uint16_t width = 832;
	uint8_t height = 5;

	m_borders.resize(m_numberOfBorders);

	m_upperBorder.setPosition(sf::Vector2f(m_border, m_border - height));
	m_borders[0] = new Hitbox(m_upperBorder, width, height);

	m_lowerBorder.setPosition(sf::Vector2f(m_border, m_border + width));
	m_borders[1] = new Hitbox(m_lowerBorder, width, height);

	m_leftBorder.setPosition(sf::Vector2f(m_border - height, m_border));
	m_borders[2] = new Hitbox(m_leftBorder, height, width);

	m_rightBorder.setPosition(sf::Vector2f(m_border + width, m_border));
	m_borders[3] = new Hitbox(m_rightBorder, height, width);
}

void TileMap::LoadFromFile(const std::string& fileName)
{
	std::ifstream in (fileName);

	if (in.is_open())
	{
		uint8_t tileSize = 32;
		for (uint16_t y = 0; y < m_height; y++)
		{
			for (uint16_t x = 0; x < m_width; x++)

			{
				int tileType;
				in >> tileType;

				switch (tileType)
				{
				case 0: break;

				case 1:
				{
					m_map[x][y] = new Brick(x * tileSize + m_border, y * tileSize + m_border, m_textures["BRICK"]);
					break;
				}
				case 2:
				{
					m_map[x][y] = new Steel(x * tileSize + m_border, y * tileSize + m_border, m_textures["STEEL"]);
					break;
				}
				case 3:
				{
					m_map[x][y] = new Water(x * tileSize + m_border, y * tileSize + m_border, m_textures["WATER"]);
					break;
				}
				case 4:
				{
					m_map[x][y] = new Ice(x * tileSize + m_border, y * tileSize + m_border, m_textures["ICE"]);
					break;
				}
				case 5:
				{
					m_map[x][y] = new Trees(x * tileSize + m_border, y * tileSize + m_border, m_textures["TREES"]);
					break;
				}
				default:
				{
					throw "ERROR::TILE_MAP::INVALID_TILE_TYPE";
					break;
				}
				}
			}
		}
	}
	else
	{
		throw "ERROR::TILE_MAP::COULD NOT LOAD FROM FILE::FILENAME: " + fileName;
	}

	in.close();
}

void TileMap::AddTexture(const std::string& textureName,const sf::Texture& texture)
{
	m_textures[textureName] = texture;
}

void TileMap::Render(sf::RenderTarget* target)
{
	for (uint16_t x = 0; x < m_height; ++x)
		for (uint16_t y = 0; y < m_width; ++y)
			if(m_map[x][y]!=NULL)
				m_map[x][y]->Render(target);

	for (uint16_t i = 0; i < m_numberOfBorders; ++i)
		m_borders[i]->Render(target);
}
