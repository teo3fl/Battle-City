#include "stdafx.h"
#include "Tank.h"

Tank::Tank()
{
	m_bullet = nullptr;
	m_dropPowerUp = false;
	m_bulletHealth = 1;

	m_timer = 0;
	ChangeMaxTimer();

	dirX = 0;
	dirY = 1;
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

std::string Tank::GetType() const
{
	return m_type;
}

bool Tank::DropPowerUp()
{
	return m_dropPowerUp;
}

void Tank::SetDropPowerUp()
{
	m_dropPowerUp = true;
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

void Tank::DestroyBullet(Bullet* bullet)
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
		m_bullet = CreateBullet();
}

std::pair<int, int> Tank::GenerateMovementDirection()
{
	static int option = 0;

	int x = 0;
	int y = 0;

	switch ((option++)%4)
	{
	case 0:
	{
		x = 1;
		SetFacingDirection("RIGHT");
		break;
	}
	case 1:
	{
		x = -1;
		SetFacingDirection("LEFT");
		break;
	}
	case 2:
	{
		y = 1;
		SetFacingDirection("DOWN");
		break;
	}
	case 3:
	{
		y = -1;
		SetFacingDirection("UP");
		break;
	}
	default:
	{
		throw "ERROR::TANK::INVALID_OPTION";
		break;
	}
	}

	return std::make_pair(x, y);
}

bool Tank::SwitchMovementDirection(const float& dt)
{
	m_timer += dt;
	if (m_timer >= m_maxTimer)
	{
		m_timer = 0;
		ChangeMaxTimer();
		return true;
	}
	return false;
}

void Tank::ChangeMaxTimer()
{
	srand(NULL);
	m_maxTimer = rand()%5+3;
}

void Tank::Update(const float& dt)
{
	if (SwitchMovementDirection(dt))
	{
		std::pair<int,int> pair = std::move(GenerateMovementDirection());
		dirX = pair.first;
		dirY = pair.second;
	}
	Fire();
	m_movementComponent->Move(dirX, dirY, dt);

	m_movementComponent->Update(dt);
	m_hitbox->Update();
}

Bullet* Tank::CreateBullet()
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

	return new Bullet(bulletX, bulletY, m_bulletHealth, dir, m_textures[ss.str()], m_bulletType, BulletSource::Enemy);
}
