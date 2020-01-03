#include "stdafx.h"
#include "BasicTank.h"

BasicTank::BasicTank() : Tank()
{
	m_movementSpeed = 50.f; 
	m_points = 100;
	m_health = 1;
	m_bulletSpeed = 50.f;
	m_bulletType = BulletType::Slow;

	m_facingDirection = "DOWN";

	CreateHitbox(m_sprite, 53, 53);
	CreateMovementComponent(m_movementSpeed, 500.f, 300.f);
}