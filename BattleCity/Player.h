#pragma once
#include "Tank.h"
#include "Entity.h"

class Player : public Tank
{
public:
	Player(const std::string& name, float x, float y);

	void IncreaseScore(uint8_t points);
	const std::string GetName();
	const uint16_t GetLives();
	const uint32_t GetScore();	

private:
	std::string m_name;
	uint16_t m_lives : 9;
	uint32_t m_score : 24;
	uint8_t m_health : 1;
	uint8_t m_offensivePower : 2;
};

