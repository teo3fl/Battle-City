#include "stdafx.h"
#include "Ice.h"

Ice::Ice(int x, int y, const sf::Texture& texture) : Tile(x, y, texture)
{
	CreateHitbox(m_sprite);
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