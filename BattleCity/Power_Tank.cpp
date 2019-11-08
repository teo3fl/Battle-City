#include "Power_Tank.h"

std::string PowerTank::GetName() const
{
	return m_name;
}

uint16_t PowerTank::GetPoints() const
{
	return m_points;
}

uint8_t PowerTank::GetHealth() const
{
	return m_health;
}

uint8_t PowerTank::GetMovement() const
{
	return m_movement;
}

uint8_t PowerTank::GetBullet() const
{
	return m_bullet;
}
