#include "stdafx.h"
#include "Tank.h"

Tank::Tank()
{
	m_bullet = nullptr;
}

Tank::~Tank()
{
	if (m_bullet)
		delete m_bullet;
}

uint16_t Tank::GetPoints() const
{
	return m_points;
}

uint8_t Tank::GetHealth() const
{
	return m_health;
}

float Tank::GetMovement() const
{
	return m_movementSpeed;
}

Bullet* Tank::GetBullet() const
{
	if (m_bullet)
		return m_bullet;
	return nullptr;
}

void Tank::SetFacingDirection(const std::string& direction)
{
	m_facingDirection = direction;
	SetTexture(direction);
}

void Tank::DecreaseHealth(uint8_t value)
{
	m_health -= value;
}

void Tank::DestroyBullet()
{
	if (m_bullet)
	{
		delete m_bullet;
		m_bullet = nullptr;
	}
}

void Tank::Fire()
{
	if (!m_bullet)
	{
		sf::Vector2f tankPosition = GetPosition();
		sf::FloatRect tankDimensions = GetGlobalBounds();
		float bulletX = tankPosition.x + tankDimensions.width / 2.f;
		float bulletY = tankPosition.y + tankDimensions.height / 2.f;

		std::stringstream ss;
		ss << "BULLET_" << m_facingDirection;

		sf::Vector2f dir(0.f, 0.f);

		if (m_facingDirection == "UP")
			dir.y = -1.f;
		if (m_facingDirection == "DOWN")
			dir.y = 1.f;
		if (m_facingDirection == "LEFT")
			dir.x = -1.f;
		if (m_facingDirection == "RIGHT")
			dir.x = 1.f;

		m_bullet = new Bullet(bulletX, bulletY, dir, m_textures[ss.str()], m_bulletType, BulletSource::Enemy);
	}
}
