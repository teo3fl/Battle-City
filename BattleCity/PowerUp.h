#pragma once 

#include "BasicTile.h"

enum class PowerUpType
{
	Grenade,
	Helmet,
	Shovel,
	Star,
	Tank,
	Timer
};

class PowerUp : public BasicTile
{

public:
	PowerUp(sf::Vector2f coordinates, const sf::Texture& texture, PowerUpType type);

	PowerUpType GetType();
	uint16_t GetPoints();

	bool Update(const float dt);

private:
	PowerUpType m_type : 3;
	uint16_t m_points;
	float m_timer;
	float m_maxTime;
};