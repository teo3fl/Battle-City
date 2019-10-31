#include "Tile.h"

Tile::Tile(TileType type)
{
	m_type = type;
	switch (type)
	{
	case TileType::BrWall:
	{
		m_isPassable = false;
		m_isBreakable = true;
		m_health = 1;
		break;
	}
	case TileType::StWall:
	{
		m_isPassable = false;
		m_isBreakable = true;
		m_health = 2;
		break;
	}
	case TileType::Trees:
	{
		m_isPassable = true;
		m_isBreakable = false;
		m_health = 0;
		break;
	}
	case TileType::Water:
	{
		m_isPassable = false;
		m_isBreakable = false;
		m_health = 0;
		break;
	}
	case TileType::Ice:
	{
		m_isPassable = true;
		m_isBreakable = false;
		m_health = 0;
		break;
	}
	}
}

Tile::TileType Tile::GetType() const
{
	return m_type;
}

bool Tile::IsPassable() const
{
	return m_isPassable;
}

bool Tile::IsBreakable() const
{
	return m_isBreakable;
}

uint8_t Tile::GetHealth() const
{
	return m_health;
}

void Tile::SetHealth(uint8_t health)
{
	m_health = health;
}


