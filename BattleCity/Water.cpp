#include "stdafx.h"
#include "Water.h"

Water::Water(int x, int y, const sf::Texture& texture) : Tile(x, y, texture)
{
	CreateHitbox(m_sprite);
}

const std::string Water::GetType() const
{
	return m_type;
}

bool Water::IsPassable() const
{
	return m_isPassable;
}

bool Water::IsBreakable() const
{
	return m_isBreakable;
}
