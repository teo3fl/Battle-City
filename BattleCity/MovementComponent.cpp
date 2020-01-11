#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite,
	float maxVelocity, float acceleration, float deceleration)
	: m_sprite(sprite),
	m_maxVelocity(maxVelocity), m_acceleration(acceleration), m_deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{

}

//Accessors
const float& MovementComponent::GetMaxVelocity() const
{
	return m_maxVelocity;
}

const sf::Vector2f& MovementComponent::GetVelocity() const
{
	return m_velocity;
}

void MovementComponent::StopVelocity()
{
	/* Resets the velocity to 0.*/

	m_velocity.x = 0.f;
	m_velocity.y = 0.f;
}

void MovementComponent::StopVelocityX()
{
	/* Resets the velocity x to 0.*/

	m_velocity.x = 0.f;
}

void MovementComponent::StopVelocityY()
{
	/* Resets the velocity y to 0.*/

	m_velocity.y = 0.f;
}

void MovementComponent::Push(sf::Vector2f direction, const float& dt)
{
	m_velocity.x += m_acceleration * direction.x * dt;
	m_velocity.y += m_acceleration * direction.y * dt;
}

void MovementComponent::SetDeceleration(uint16_t value)
{
	m_deceleration = value;
}

void MovementComponent::Move(const float dir_x, const float dir_y, const float& dt)
{
	/* Accelerating a sprite until it reaches the max velocity. */

	m_velocity.x += m_acceleration * dir_x * dt;
	m_velocity.y += m_acceleration * dir_y * dt;
}

void MovementComponent::Update(const float& dt)
{
	/*
	Decelerates the sprite and controls the maximum velocity.
	Moves the sprite.
	*/

	if (m_velocity.x > 0.f) //Check for positive x
	{
		//Max velocity check
		if (m_velocity.x > m_maxVelocity)
			m_velocity.x = m_maxVelocity;

		//Deceleration
		m_velocity.x -= m_deceleration * dt;
		if (m_velocity.x < 0.f)
			m_velocity.x = 0.f;
	}
	else if (m_velocity.x < 0.f) //Check for negative x
	{
		//Max velocity check
		if (m_velocity.x < -m_maxVelocity)
			m_velocity.x = -m_maxVelocity;

		//Deceleration
		m_velocity.x += m_deceleration * dt;
		if (m_velocity.x > 0.f)
			m_velocity.x = 0.f;
	}

	if (m_velocity.y > 0.f) //Check for positive y
	{
		//Max velocity check
		if (m_velocity.y > m_maxVelocity)
			m_velocity.y = m_maxVelocity;

		//Deceleration
		m_velocity.y -= m_deceleration * dt;
		if (m_velocity.y < 0.f)
			m_velocity.y = 0.f;
	}
	else if (m_velocity.y < 0.f) //Check for negative y
	{
		//Max velocity check
		if (m_velocity.y < -m_maxVelocity)
			m_velocity.y = -m_maxVelocity;

		//Deceleration
		m_velocity.y += m_deceleration * dt;
		if (m_velocity.y > 0.f)
			m_velocity.y = 0.f;
	}
	
	//Final move
	m_sprite.move(m_velocity * dt); //Uses velocity
}
