#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(float x, float y, sf::Vector2f direction, const sf::Texture& texture, BulletType type, BulletSource source)
	: m_type(type), m_source(source), m_direction(direction)
{
	m_sprite.setScale(0.4f, 0.4f);
	SetSpeed();
	SetPosition(x, y);
	SetTexture(texture);
	CreateHitbox(m_sprite, 
		m_sprite.getGlobalBounds().width,
		m_sprite.getGlobalBounds().height
	);
	CreateMovementComponent(m_movementSpeed, 900.f, 0.f);
}

Bullet::~Bullet()
{
	
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

void Bullet::Update(const float& dt)
{
	m_movementComponent->Move(m_direction.x, m_direction.y, dt);
	m_movementComponent->Update(dt);

	m_hitbox->Update();
}

void Bullet::Render(sf::RenderTarget* target)
{
	target->draw(m_sprite);

	m_hitbox->Render(target);
}
