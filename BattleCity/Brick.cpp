#include "stdafx.h"
#include "Brick.h"

Brick::Brick(int x, int y, const sf::Texture& texture) : Tile(x, y, texture)
{
	CreateHitbox(m_sprite);
	m_bulletCollision = true;
	m_tankCollision = true;
	m_type = "Brick";
}

