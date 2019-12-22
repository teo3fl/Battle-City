#include "Steel.h"

Steel::Steel(const float x, const float y, const sf::Texture& texture) : Tile(x, y, texture)
{
}

const std::string Steel::GetType() const
{
	return m_type;
}

bool Steel::IsPassable() const
{
	return m_isPassable;
}

bool Steel::IsBreakable() const
{
	return m_isBreakable;
}
