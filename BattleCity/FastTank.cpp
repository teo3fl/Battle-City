#include "stdafx.h"
#include "FastTank.h"

std::string FastTank::GetName() const
{
	return m_name;
}

uint16_t FastTank::GetPoints() const
{
	return m_points;
}

uint8_t FastTank::GetHealth() const
{
	return m_health;
}

uint8_t FastTank::GetMovement() const
{
	return m_movement;
}

uint8_t FastTank::GetBullet() const
{
	return m_bullet;
}
