#include "Trees.h"

Trees::Trees(int x, int y, const sf::Texture& texture) : Tile(x, y, texture)
{
}

const std::string Trees::GetType() const
{
	return m_type;
}

bool Trees::IsPassable() const
{
	return m_isPassable;
}

bool Trees::IsBreakable() const
{
	return m_isBreakable;
}
