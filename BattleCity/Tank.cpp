#include "stdafx.h"
#include "Tank.h"

Tank::Tank()
{
	m_bullet = nullptr;
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
	sf::Vector2f tankPosition = GetPosition();
	sf::FloatRect tankDimensions = GetGlobalBounds();
	float bulletX = tankPosition.x + tankDimensions.width / 2.f;
	float bulletY = tankPosition.y + tankDimensions.height / 2.f;

	std::string direction = m_movementComponent->GetFacingDirection();

	std::stringstream ss;
	ss << "BULLET_" << direction;

	sf::Vector2f dir (0.f, 0.f);

	if (direction == "UP")
		dir.y = -1.f;
	if (direction == "DOWN")
		dir.y = 1.f;
	if (direction == "LEFT")
		dir.x = -1.f;
	if (direction == "RIGHT")
		dir.x = 1.f;

	m_bullet = new Bullet(bulletX, bulletY, dir, m_textures[ss.str()], m_bulletType, BulletSource::Enemy);
}
