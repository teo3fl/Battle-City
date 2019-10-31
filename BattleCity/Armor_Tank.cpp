#include "Armor_Tank.h"

std::string Armor_Tank::GetName() const
{
	return m_name;
}

uint16_t Armor_Tank::GetPoints() const
{
	return m_points;
}

uint8_t Armor_Tank::GetHealth() const
{
	return m_health;
}

uint8_t Armor_Tank::GetMovement() const
{
	return m_movement;
}

uint8_t Armor_Tank::GetBullet() const
{
	return m_bullet;
}
