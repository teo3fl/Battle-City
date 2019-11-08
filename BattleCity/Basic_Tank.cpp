#include "Basic_Tank.h"

std::string BasicTank::GetName() const
{
	return m_name;
}

uint16_t BasicTank::GetPoints() const
{
	return m_points;
}

uint8_t BasicTank::GetHealth() const
{
	return m_health;
}

uint8_t BasicTank::GetMovement() const
{
	return m_movement;
}

uint8_t BasicTank::GetBullet() const
{
	return m_bullet;
}
