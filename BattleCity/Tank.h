#pragma once

#include "Entity.h" 

class Tank : public Entity
{
public :
	virtual uint16_t GetPoints() const;
	virtual uint8_t GetHealth() const;
	virtual float GetMovement() const; // returns the movement speed of the tank;
	virtual float GetBullet() const;  // returns the velocity of the projectile
protected:
	uint16_t m_points;
	uint8_t m_health;
	float m_bulletVelocity;
};

