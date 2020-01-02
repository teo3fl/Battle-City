#pragma once

#include "Bullet.h"

class Tank : public Entity
{
public :
	Tank();
	virtual ~Tank();
	virtual uint16_t GetPoints() const;
	virtual uint8_t GetHealth() const;
	virtual float GetMovement() const; // returns the movement speed of the tank;
	virtual Bullet* GetBullet() const; 

	void SetFacingDirection(const std::string& direction);

	void DestroyBullet();

	void Fire();
protected:
	uint16_t m_points;
	uint8_t m_health;

	float m_bulletSpeed;
	BulletType m_bulletType;
	Bullet* m_bullet;

	std::string m_facingDirection;
};

