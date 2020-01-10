#include "stdafx.h"
#include "PowerTank.h"

PowerTank::PowerTank() : Tank()
{
	m_type = "PowerTank";
	m_movementSpeed = 120.f;
	m_points = 300;
	m_health = 1;
	m_bulletType = BulletType::Fast;

	m_facingDirection = "DOWN";

	CreateHitbox(m_sprite, 53, 53);
	CreateMovementComponent(m_movementSpeed, 500.f, 300.f);
}
