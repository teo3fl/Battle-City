#include "stdafx.h"
#include "BasicTank.h"

BasicTank::BasicTank() : Tank()
{
	m_type = "BasicTank";
	m_movementSpeed = 75.f; 
	m_points = 100;
	m_health = 1;
	m_bulletType = BulletType::Slow;

	m_facingDirection = "DOWN";

	CreateHitbox(m_sprite, 53, 53);
	CreateMovementComponent(m_movementSpeed, 500.f, 300.f);
}