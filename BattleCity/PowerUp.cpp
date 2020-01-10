#include "stdafx.h"
#include "PowerUp.h"

PowerUp::PowerUp(sf::Vector2f coordinates, const sf::Texture& texture, PowerUpType type)
	: BasicTile (coordinates.x,coordinates.y,texture), m_type(type)
{
	m_height = 60;
	m_width = 60;
	m_sprite.scale(2.f, 2.f);
	CreateHitbox(m_sprite);

	m_timer = 0;
	m_maxTime = 20;
	m_points = 500;
}

PowerUpType PowerUp::GetType()
{
	return m_type;
}

uint16_t PowerUp::GetPoints()
{
	return m_points;
}

bool PowerUp::Update(const float dt)
{
	m_timer += dt;
	if (m_timer >= m_maxTime)
		return false;
	return true;
}
