#include "stdafx.h"
#include "FastTank.h"

FastTank::FastTank() : Tank()
{
	m_type = "FastTank";
	m_movementSpeed = 100.f; 
	m_points = 200;
	m_health = 1;
	m_bulletSpeed = 75.f;
	m_bulletType = BulletType::Normal;

	m_facingDirection = "DOWN";

	CreateHitbox(m_sprite, 53, 53);
	CreateMovementComponent(m_movementSpeed, 500.f, 300.f);
}