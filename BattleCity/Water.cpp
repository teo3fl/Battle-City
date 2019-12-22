#include "Water.h"

Water::Water(const float x, const float y, const sf::Texture& texture) : Tile(x, y, texture)
{
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
