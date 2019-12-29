#include "stdafx.h"
#include "ArmorTank.h"

std::string ArmorTank::GetName() const
{
	return m_name;
}

uint16_t ArmorTank::GetPoints() const
{
	return m_points;
}

uint8_t ArmorTank::GetHealth() const
{
	return m_health;
}

uint8_t ArmorTank::GetMovement() const
{
	return m_movement;
}

uint8_t ArmorTank::GetBullet() const
{
	return m_bullet;
}
