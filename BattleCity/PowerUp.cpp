#include "stdafx.h"
#include "PowerUp.h"

PowerUp::PowerUp(sf::Vector2f coordinates, const sf::Texture& texture, PowerUpType type)
	: BasicTile (coordinates.x,coordinates.y,texture), m_type(type)
{
}

PowerUpType PowerUp::GetType()
{
	return m_type;
}
