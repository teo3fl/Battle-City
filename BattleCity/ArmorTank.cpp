#include "stdafx.h"
#include "ArmorTank.h"

ArmorTank::ArmorTank() : Tank()
{
	m_movementSpeed = 75.f;
	m_points = 400;
	m_health = 4;
	m_bulletSpeed = 75.f;
	m_bulletType = BulletType::Normal;
}