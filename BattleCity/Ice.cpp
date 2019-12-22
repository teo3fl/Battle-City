#include "Ice.h"

Ice::Ice(const float x, const float y, const sf::Texture& texture) : Tile(x, y, texture)
{
}

const std::string Ice::GetType() const
{
	return m_type;
}

bool Ice::IsPassable() const
{
	return m_isPassable;
}

bool Ice::IsBreakable() const
{
	return m_isBreakable;
}