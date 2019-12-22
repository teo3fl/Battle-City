#include "Player.h"

Player::Player(float x, float y)
{
	// create hitbox
	SetPosition(x, y);
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
