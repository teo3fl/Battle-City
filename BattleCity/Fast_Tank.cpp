#include "Fast_Tank.h"

std::string Fast_Tank::GetName() const
{
	return m_name;
}

uint16_t Fast_Tank::GetPoints() const
{
	return m_points;
}

uint8_t Fast_Tank::GetHealth() const
{
	return m_health;
}

uint8_t Fast_Tank::GetMovement() const
{
	return m_movement;
}

uint8_t Fast_Tank::GetBullet() const
{
	return m_bullet;
}
