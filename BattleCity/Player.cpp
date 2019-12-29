#include "stdafx.h"
#include "Player.h"

Player::Player(const std::string& name, float x, float y) : m_name(name)
{
	// create hitbox
	SetPosition(x, y);
	m_sprite.scale(sf::Vector2f(0.6f, 0.6f));
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

const uint8_t Player::GetHealth()
{
	return m_health;
}

const uint8_t Player::GetMovement()
{
	return m_movement;
}

const uint8_t Player::GetBullet()
{
	return m_bullet;
}

const uint8_t Player::GetOffensivePower()
{
	return m_offensivePower;
}
