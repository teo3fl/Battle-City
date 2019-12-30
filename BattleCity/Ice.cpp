#include "stdafx.h"
#include "Ice.h"

Ice::Ice(int x, int y, const sf::Texture& texture) : Tile(x, y, texture)
{
	CreateHitbox(m_sprite);
	m_bulletCollision = false;
	m_tankCollision = false;
	m_type = "Ice";
}