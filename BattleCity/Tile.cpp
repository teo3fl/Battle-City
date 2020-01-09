#include "stdafx.h"
#include "Tile.h"

Tile::Tile(int x, int y, const sf::Texture& texture)
	: BasicTile(x,y,texture)
{
	m_width = 30;
	m_height = 30;
}


const uint8_t Tile::GetHealth()
{
	return NULL;
}

std::string& Tile::GetType()
{
	return m_type;
}

bool Tile::GetTankCollision()
{
	return m_tankCollision;
}

bool Tile::GetBulletCollision()
{
	return m_bulletCollision;
}
