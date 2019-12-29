#include "stdafx.h"
#include "Player.h"

Player::Player(const std::string& name, float x, float y) : m_name(name)
{
	m_movementSpeed = 50.f; 
	m_health = 1;
	m_lives = 3;
	m_bulletVelocity = 100.f;
	m_offensivePower = 0;

	SetPosition(x, y);
	m_sprite.scale(sf::Vector2f(0.6f, 0.6f));

	CreateHitbox(m_sprite, 53, 53);
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

const uint8_t Player::GetOffensivePower()
{
	return m_offensivePower;
}

void Player::Update(const float& dt)
{
	m_hitbox->Update();
}

void Player::Render(sf::RenderTarget* target)
{
	target->draw(m_sprite);

	m_hitbox->Render(target);
}
