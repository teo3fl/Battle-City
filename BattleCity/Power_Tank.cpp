#include "Power_Tank.h"

std::string Power_Tank::GetName() const
{
	return m_name;
}

uint16_t Power_Tank::GetPoints() const
{
	return m_points;
}

uint8_t Power_Tank::GetHealth() const
{
	return m_health;
}

uint8_t Power_Tank::GetMovement() const
{
	return m_movement;
}

uint8_t Power_Tank::GetBullet() const
{
	return m_bullet;
}
