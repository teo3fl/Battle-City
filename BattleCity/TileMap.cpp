#include "TileMap.h"
#include <fstream>

TileMap::TileMap(float width, float height) :
	m_width(width), m_height(height)
{
	m_map.resize(m_height);
	for (int x = 0; x < m_height; x++)
		m_map[x].resize(m_width);
}

void TileMap::LoadFromFile(const std::string& fileName)
{
	std::ifstream in;

	in.open(fileName);

	if (in.is_open())
	{
		for (int x = 0; x < m_height; x++)
		{
			for (int y = 0; y < m_width; y++)

			{
				uint8_t tileType;
				in >> tileType;

				switch (tileType)
				{
				case 0: break;

				case 1:
				{
					m_map[x][y].push_back(new Brick(x * 64 + m_border, y * 64 + m_border, m_textures["BRICK"]));
					break;
				}
				case 2:
				{
					m_map[x][y].push_back(new Steel(x * 64 + m_border, y * 64 + m_border, m_textures["STEEL"]));
					break;
				}
				case 3:
				{
					m_map[x][y].push_back(new Water(x * 64 + m_border, y * 64 + m_border, m_textures["WATER"]));
					break;
				}
				case 4:
				{
					m_map[x][y].push_back(new Ice(x * 64 + m_border, y * 64 + m_border, m_textures["ICE"]));
					break;
				}
				case 5:
				{
					m_map[x][y].push_back(new Trees(x * 64 + m_border, y * 64 + m_border, m_textures["TREES"]));
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
