#include "stdafx.h"
#include "Tank.h"

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

float Tank::GetBullet() const
{
	return m_bulletVelocity;
}
