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
	virtual std::string GetType() const;

	bool DropPowerUp();
	void SetDropPowerUp();

	void SetFacingDirection(const std::string& direction);
	virtual void DecreaseHealth(uint8_t value); 
	virtual void DestroyBullet(Bullet* bullet);

	virtual void Fire();
	std::pair<int,int> GenerateMovementDirection();
	bool SwitchMovementDirection(const float& dt);
	void ChangeMaxTimer();

	virtual void Update(const float& dt) override;

protected:
	Bullet* CreateBullet();

protected:
	std::string m_type;
	uint16_t m_points;
	uint8_t m_health : 1;
	bool m_dropPowerUp;

	uint8_t m_bulletHealth : 2;
	BulletType m_bulletType;
	Bullet* m_bullet;

	std::string m_facingDirection;

	float m_timer;
	float m_maxTimer;

	int dirX;
	int dirY;
};

