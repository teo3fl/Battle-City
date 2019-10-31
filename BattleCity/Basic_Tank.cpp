#include "Basic_Tank.h"

std::string Basic_Tank::GetName() const
{
	return m_name;
}

uint16_t Basic_Tank::GetPoints() const
{
	return m_points;
}

uint8_t Basic_Tank::GetHealth() const
{
	return m_health;
}

uint8_t Basic_Tank::GetMovement() const
{
	return m_movement;
}

uint8_t Basic_Tank::GetBullet() const
{
	return m_bullet;
}
