#pragma once
#include "Tank.h"

class ArmorTank : public Tank
{
public:
	std::string GetName() const override;
	uint16_t GetPoints() const override;
	uint8_t GetHealth() const override;
	uint8_t GetMovement() const override;
	uint8_t GetBullet() const override;

private:
	const std::string m_name = "Armor_Tank";
	const uint16_t m_points = 400;
	uint8_t m_health = 4;
	const uint8_t m_movement = 2;
	const uint8_t m_bullet = 2;
};

