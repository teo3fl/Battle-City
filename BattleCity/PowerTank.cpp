#include "stdafx.h"
#include "PowerTank.h"

PowerTank::PowerTank() : Tank()
{
	m_movementSpeed = 75.f;
	m_points = 300;
	m_health = 1;
	m_bulletSpeed = 100.f;
	m_bulletType = BulletType::Fast;
}
