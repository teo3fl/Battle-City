#include "stdafx.h"
#include "PowerUp.h"

PowerUp::PowerUp(sf::Vector2f coordinates, const sf::Texture& texture, PowerUpType type)
	: BasicTile (coordinates.x,coordinates.y,texture), m_type(type)
{
	m_height = 60;
	m_width = 60;
	CreateHitbox(m_sprite);
}

PowerUpType PowerUp::GetType()
{
	return m_type;
}
