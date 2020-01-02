#include "stdafx.h"
#include "Brick.h"

Brick::Brick(int x, int y, const sf::Texture& texture) : Tile(x, y, texture)
{
	m_width = 15;
	m_height = 15;
	m_sprite.scale(0.5f, 0.5f);
	CreateHitbox(m_sprite);
	m_bulletCollision = true;
	m_tankCollision = true;
	m_type = "Brick";
}

const uint8_t Brick::GetHealth()
{
	return 1;
}

