#include "stdafx.h"
#include "Base.h"

Base::Base(int x, int y, const sf::Texture& texture) : Tile(x,y,texture)
{
	m_width = 60;
	m_height = 60;
	CreateHitbox(m_sprite);
	m_bulletCollision = true;
	m_tankCollision = true;
	m_type = "Base";
}
