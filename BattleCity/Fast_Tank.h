#pragma once
#include "Tank.h"

class Fast_Tank : public Tank
{
public:
	std::string GetName() const override;
	uint16_t GetPoints() const override;
	uint8_t GetHealth() const override;
	uint8_t GetMovement() const override;
	uint8_t GetBullet() const override;

private:
	const std::string m_name = "Fast Tank";
	const uint16_t m_points = 200;
	const uint8_t m_health = 1;
	const uint8_t m_movement = 3;
	const uint8_t m_bullet = 2;
};

