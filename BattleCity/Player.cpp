#include "stdafx.h"
#include "Player.h"

Player::Player(const std::string& name, float x, float y) : Tank(), m_name(name)
{
	m_health = 1;
	m_lives = 3;
	m_offensivePower = 0;
	UpdateOffensivePower();
	m_secondaryBullet = NULL;
	m_score = 0;
	m_protected = true;
	m_protectedTime = 0;
	m_maxProtectedTime = 10;
	m_movementSpeed = 90.f;

	m_facingDirection = "UP";

	SetPosition(x, y);
	m_sprite.scale(sf::Vector2f(0.6f, 0.6f));

	CreateHitbox(m_sprite, 53, 53);
	CreateMovementComponent(m_movementSpeed,500.f,300.f);
}

void Player::IncreaseScore(uint16_t points)
{
	m_score += points;
}

void Player::IncreaseOffensivePower()
{
	if (m_offensivePower < 3)
	{
		++m_offensivePower;
		UpdateOffensivePower();
	}
}

void Player::GiveExtraLife()
{
	++m_lives;
}

void Player::ResetOffensivePower()
{
	if (m_offensivePower)
	{
		m_offensivePower = 0;
		UpdateOffensivePower();
	}
}

void Player::UpdateOffensivePower()
{
	switch (m_offensivePower)
	{
	case 0:
	{
		m_bulletType = BulletType::Normal;
		m_enableSecondBullet = false;
		break;
	}
	case 1:
	{
		m_bulletType = BulletType::Fast;
		break;
	}
	case 2:
	{
		m_enableSecondBullet = true;
		break;
	}
	case 3:
	{
		m_bulletHealth = 2;
	}
	}
}

void Player::Fire()
{
	if (!m_bullet)
 		m_bullet = CreateBullet();
	else
		if (m_enableSecondBullet && !m_secondaryBullet)
			m_secondaryBullet = CreateBullet();
}

void Player::SetProtected()
{
	m_protected = true;
}

void Player::SetTexture(const std::string& texture)
{
	if (m_protected)
		m_sprite.setTexture(m_textures[texture + "_PROTECTED"]);
	else
		m_sprite.setTexture(m_textures[texture]);
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

bool Player::CanFireSecondaryBullet()
{
	return m_enableSecondBullet;
}

Bullet* Player::GetSecondaryBullet() const
{
	if (m_secondaryBullet)
		return m_secondaryBullet;
	return nullptr;
}

void Player::DestroyBullet(Bullet* bullet)
{
	if (m_bullet && m_bullet == bullet)
	{
		delete m_bullet;
		m_bullet = nullptr;
	}
	else
		if (m_secondaryBullet && m_secondaryBullet == bullet)
		{
			delete m_secondaryBullet;
			m_secondaryBullet = nullptr;
		}

}

bool Player::IsProtected()
{
	return m_protected;
}

void Player::UpdateProtection(const float& dt)
{
	m_protectedTime += dt;
	if (m_protectedTime >= m_maxProtectedTime)
	{
		m_protected = false;
		m_protectedTime = 0;
	}
}

void Player::Update(const float& dt)
{
	m_movementComponent->Update(dt);
	m_hitbox->Update();
	if (m_protected)
		UpdateProtection(dt);
}

