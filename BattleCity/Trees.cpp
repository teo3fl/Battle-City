#include "stdafx.h"
#include "Trees.h"

Trees::Trees(int x, int y, const sf::Texture& texture) : Tile(x, y, texture)
{
	m_bulletCollision = false;
	m_tankCollision = false;
	m_type = "Trees";
}
