#include "stdafx.h"
#include "Steel.h"

Steel::Steel(int x, int y, const sf::Texture& texture) : Tile(x, y, texture)
{
	CreateHitbox(m_sprite);
	m_bulletCollision = true;
	m_tankCollision = true; 
	m_type = "Steel";
}

const uint8_t Steel::GetHealth()
{
	return 2;
}
