#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(uint16_t width, uint16_t height) :
	m_width(width), m_height(height)
{
	m_border = 80;

	m_map.resize(m_height);
	for (int x = 0; x < m_height; x++)
		m_map[x].resize(m_width);
}

TileMap::~TileMap()
{
	for (int x = 0; x < m_height; x++)
		for (int y = 0; y < m_width; y++)
			if (m_map[x][y])
				delete m_map[x][y];
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
}
