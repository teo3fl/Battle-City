#include "stdafx.h"
#include "Water.h"

Water::Water(int x, int y, const sf::Texture& texture) : Tile(x, y, texture)
{
	CreateHitbox(m_sprite);
	m_bulletCollision = false;
	m_tankCollision = true;
	m_type = "Water";
}
