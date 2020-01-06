#include "stdafx.h"
#include "ArmorTank.h"

ArmorTank::ArmorTank() : Tank()
{
	m_type = "ArmorTank";
	m_movementSpeed = 75.f;
	m_points = 400;
	m_health = 4;
	m_bulletSpeed = 75.f;
	m_bulletType = BulletType::Normal;

	m_facingDirection = "DOWN";

	CreateHitbox(m_sprite, 53, 53);
	CreateMovementComponent(m_movementSpeed, 500.f, 300.f);
}