#include "stdafx.h"
#include "Player.h"

Player::Player(const std::string& name, float x, float y) : Tank(), m_name(name)
{
	m_movementSpeed = 60.f; 
	m_health = 1;
	m_lives = 3;
	m_bulletSpeed = 100.f;
	m_offensivePower = 0;
	m_bulletType = BulletType::Normal;

	m_facingDirection = "UP";

	SetPosition(x, y);
	m_sprite.scale(sf::Vector2f(0.6f, 0.6f));

	CreateHitbox(m_sprite, 53, 53);
	CreateMovementComponent(m_movementSpeed,500.f,300.f);
}

const std::string Player::GetName()
{
	return m_name;
}

const uint16_t Player::GetLives()
{
	return m_lives;
}

const uint32_t Player::GetScore()
{
	return m_score;
}

