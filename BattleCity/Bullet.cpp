#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(float x, float y, float direction, const sf::Texture& texture, BulletType type, BulletSource source)
	: m_type(type), m_source(source)
{
	SetSpeed();
	SetTexture(texture);
	CreateHitbox(m_sprite, 10, 20);
	SetPosition(x, y);
}

void Bullet::SetSpeed()
{
	switch (m_type)
	{
	case BulletType::Slow:
	{
		m_movementSpeed = 50.f;
		break;
	}
	case BulletType::Normal:
	{
		m_movementSpeed = 75.f;
		break;
	}
	case BulletType::Fast:
	{
		m_movementSpeed = 100.f;
		break;
	}
	default:
	{
		throw "BULLET::INVALID_BULLET_TYPE";
	}
	}
}

BulletSource Bullet::GetSource()
{
	return m_source;
}

uint8_t Bullet::GetHealth()
{
	return m_health;
}
