#pragma once
#include "Tank.h"
#include "Entity.h"

class Player :  public Entity
{
public:
	Player(const std::string& name, float x, float y);

	const std::string GetName();
	const uint16_t GetLives();
	const uint32_t GetScore();
	const uint8_t GetHealth();
	const uint8_t GetMovement();
	const uint8_t GetBullet();
	const uint8_t GetOffensivePower();
	

private:
	std::string m_name;
	uint16_t m_lives : 9;
	uint32_t m_score : 24;
	uint8_t m_health : 1;
	uint8_t m_movement : 1;
	uint8_t m_bullet : 1;
	uint8_t m_offensivePower : 2;
};

