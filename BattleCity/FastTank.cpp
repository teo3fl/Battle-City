#include "stdafx.h"
#include "FastTank.h"

FastTank::FastTank() : Tank()
{
	m_movementSpeed = 100.f; 
	m_points = 200;
	m_health = 1;
	m_bulletSpeed = 75.f;
	m_bulletType = BulletType::Normal;
}